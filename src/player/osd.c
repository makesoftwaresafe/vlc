/*****************************************************************************
 * player_osd.c: Player osd implementation
 *****************************************************************************
 * Copyright © 2018-2019 VLC authors and VideoLAN
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <limits.h>

#include <vlc_common.h>
#include <vlc_memstream.h>
#include <vlc_vout_osd.h>
#include "player.h"
#include "input/resource.h"

static vout_thread_t **
vlc_player_osd_HoldAll(vlc_player_t *player, size_t *count)
{
    vout_thread_t **vouts;
    input_resource_HoldVouts(player->resource, &vouts, count);

    for (size_t i = 0; i < *count; ++i)
    {
        vout_FlushSubpictureChannel(vouts[i], VOUT_SPU_CHANNEL_OSD);
        vout_FlushSubpictureChannel(vouts[i], VOUT_SPU_CHANNEL_OSD_HSLIDER);
        vout_FlushSubpictureChannel(vouts[i], VOUT_SPU_CHANNEL_OSD_HSLIDER);
    }
    return vouts;
}

static void
vlc_player_osd_ReleaseAll(vlc_player_t *player, vout_thread_t **vouts,
                            size_t count)
{
    for (size_t i = 0; i < count; ++i)
        vout_Release(vouts[i]);
    free(vouts);
    (void) player;
}

static inline void
vouts_osd_Message(vout_thread_t **vouts, size_t count, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    for (size_t i = 0; i < count; ++i)
    {
        va_list acpy;
        va_copy(acpy, args);
        vout_OSDMessageVa(vouts[i], VOUT_SPU_CHANNEL_OSD, fmt, acpy);
        va_end(acpy);
    }
    va_end(args);
}

static inline void
vouts_osd_Icon(vout_thread_t **vouts, size_t count, vlc_osd_widget_type type)
{
    for (size_t i = 0; i < count; ++i)
        vout_OSDIcon(vouts[i], VOUT_SPU_CHANNEL_OSD, type);
}

static inline void
vouts_osd_Slider(vout_thread_t **vouts, size_t count, int position, vlc_osd_widget_type type)
{
    int channel = type == OSD_HOR_SLIDER ?
        VOUT_SPU_CHANNEL_OSD_HSLIDER : VOUT_SPU_CHANNEL_OSD_VSLIDER;
    for (size_t i = 0; i < count; ++i)
        vout_OSDSlider(vouts[i], channel, position, type);
}

void
vlc_player_osd_Message(vlc_player_t *player, const char *fmt, ...)
{
    size_t count;
    vout_thread_t **vouts = vlc_player_osd_HoldAll(player, &count);

    va_list args;
    va_start(args, fmt);
    for (size_t i = 0; i < count; ++i)
    {
        va_list acpy;
        va_copy(acpy, args);
        vout_OSDMessageVa(vouts[i], VOUT_SPU_CHANNEL_OSD, fmt, acpy);
        va_end(acpy);
    }
    va_end(args);

    vlc_player_osd_ReleaseAll(player, vouts, count);
}

void
vlc_player_osd_Icon(vlc_player_t *player, vlc_osd_widget_type type)
{
    size_t count;
    vout_thread_t **vouts = vlc_player_osd_HoldAll(player, &count);

    vouts_osd_Icon(vouts, count, type);

    vlc_player_osd_ReleaseAll(player, vouts, count);
}

void
vlc_player_osd_Position(vlc_player_t *player,
                        struct vlc_player_input *input, vlc_tick_t time,
                        double position)
{
    if (input->length != VLC_TICK_INVALID)
    {
        if (time == VLC_TICK_INVALID)
            time = position * input->length;
        else
            position = time / (double) input->length;
    }

    size_t count;
    vout_thread_t **vouts = vlc_player_osd_HoldAll(player, &count);

    if (time != VLC_TICK_INVALID)
    {
        char time_text[MSTRTIME_MAX_SIZE];
        vlc_tick_to_str(time_text, time);
        if (input->length != VLC_TICK_INVALID)
        {
            char len_text[MSTRTIME_MAX_SIZE];
            vlc_tick_to_str(len_text, input->length);
            vouts_osd_Message(vouts, count, "%s / %s", time_text, len_text);
        }
        else
            vouts_osd_Message(vouts, count, "%s", time_text);
    }

    if (vlc_player_vout_IsFullscreen(player))
        vouts_osd_Slider(vouts, count, position * 100, OSD_HOR_SLIDER);
    vlc_player_osd_ReleaseAll(player, vouts, count);
}

void
vlc_player_osd_Volume(vlc_player_t *player, bool mute_action)
{
    size_t count;
    vout_thread_t **vouts = vlc_player_osd_HoldAll(player, &count);

    bool mute = vlc_player_aout_IsMuted(player);
    int volume = lroundf(vlc_player_aout_GetVolume(player) * 100.f);
    if (mute_action && mute)
        vouts_osd_Icon(vouts, count, OSD_MUTE_ICON);
    else
    {
        if (vlc_player_vout_IsFullscreen(player))
            vouts_osd_Slider(vouts, count, volume, OSD_VERT_SLIDER);
        vouts_osd_Message(vouts, count, _("Volume: %ld%%"), volume);
    }

    vlc_player_osd_ReleaseAll(player, vouts, count);
}

void
vlc_player_osd_Track(vlc_player_t *player, vlc_es_id_t *id, bool select)
{
    enum es_format_category_e cat = vlc_es_id_GetCat(id);
    const struct vlc_player_track *track = vlc_player_GetTrack(player, id);
    if (!track && select)
        return;

    const char *cat_name = es_format_category_to_string(cat);
    assert(cat_name);
    const char *track_name = select ? track->name : _("N/A");
    vlc_player_osd_Message(player, _("%s track: %s"), cat_name, track_name);
}

void
vlc_player_osd_Tracks(vlc_player_t *player, vlc_es_id_t * const *selected, vlc_es_id_t *unselect)
{
    if (!selected || !selected[0])
        return;

    const enum es_format_category_e cat = vlc_es_id_GetCat(selected[0]);
    const char *cat_name = es_format_category_to_string(cat);
    int tracks_count = 0;
    struct vlc_memstream stream;

    for (size_t i = 0; selected[i] != NULL; i++)
    {
        if (unselect != NULL
         && !strcmp(vlc_es_id_GetStrId(selected[i]), vlc_es_id_GetStrId(unselect)))
            continue;

        const struct vlc_player_track *track =
            vlc_player_GetTrack(player, selected[i]);
        /* The track can be NULL if it was terminated by the playback.
         * In this case, we have nothing to display for it. */
        if (unlikely(track == NULL))
            continue;

        /* Open the stream for the first track, and exit in case of error.
         * On the next tracks, add comma to separate the track names. */
        if (tracks_count == 0)
        {
            if (vlc_memstream_open(&stream) != 0)
                return;
        }
        else
            vlc_memstream_puts(&stream, ", ");

        vlc_memstream_puts(&stream, track->name);
        tracks_count++;
    }

    if (tracks_count == 0)
    {
        vlc_player_osd_Message(player, _("%s track: %s"), cat_name, _("N/A"));
        return;
    }

    /* The vlc_memstream is opened only if tracks_count != 0. */
    if (vlc_memstream_close(&stream) != 0)
        return;

    if (tracks_count == 1)
        vlc_player_osd_Message(player, _("%s track: %s"), cat_name,
                               stream.ptr);
    else
        vlc_player_osd_Message(player, _("%s tracks: %s"), cat_name,
                               stream.ptr);
    free(stream.ptr);
}

void
vlc_player_osd_Program(vlc_player_t *player, const char *name)
{
    vlc_player_osd_Message(player, _("Program Service ID: %s"), name);
}

static bool
vout_osd_PrintVariableText(vout_thread_t *vout, const char *varname, int vartype,
                           vlc_value_t varval, const char *osdfmt)
{
    bool found = false;
    bool isvarstring = vartype == VLC_VAR_STRING;
    size_t num_choices;
    vlc_value_t *choices;
    char **choices_text;
    var_Change(vout, varname, VLC_VAR_GETCHOICES,
               &num_choices, &choices, &choices_text);
    for (size_t i = 0; i < num_choices; ++i)
    {
        if (!found)
            if ((isvarstring &&
                 strcmp(choices[i].psz_string, varval.psz_string) == 0) ||
                (!isvarstring && choices[i].f_float == varval.f_float))
            {
                vouts_osd_Message(&vout, 1, osdfmt, choices_text[i]);
                found = true;
            }
        if (isvarstring)
            free(choices[i].psz_string);
        free(choices_text[i]);
    }
    free(choices);
    free(choices_text);
    return found;
}

int
vlc_player_vout_OSDCallback(vlc_object_t *this, const char *var,
                            vlc_value_t oldval, vlc_value_t newval, void *data)
{
    VLC_UNUSED(oldval);

    vout_thread_t *vout = (vout_thread_t *)this;

    if (strcmp(var, "aspect-ratio") == 0)
        vout_osd_PrintVariableText(vout, var, VLC_VAR_STRING,
                                   newval, _("Aspect ratio: %s"));

    else if (strcmp(var, "autoscale") == 0)
        vouts_osd_Message(&vout, 1, newval.b_bool ?
                          _("Scaled to screen") : _("Original size"));

    else if (strcmp(var, "crop") == 0)
        vout_osd_PrintVariableText(vout, var, VLC_VAR_STRING, newval,
                                   _("Crop: %s"));

    else if (strcmp(var, "crop-bottom") == 0)
        vouts_osd_Message(&vout, 1, _("Bottom crop: %d px"), newval.i_int);

    else if (strcmp(var, "crop-top") == 0)
        vouts_osd_Message(&vout, 1, _("Top crop: %d px"), newval.i_int);

    else if (strcmp(var, "crop-left") == 0)
        vouts_osd_Message(&vout, 1, _("Left crop: %d px"), newval.i_int);

    else if (strcmp(var, "crop-right") == 0)
        vouts_osd_Message(&vout, 1, _("Right crop: %d px"), newval.i_int);

    else if (strcmp(var, "deinterlace") == 0 ||
             strcmp(var, "deinterlace-mode") == 0)
    {
        bool varmode = strcmp(var, "deinterlace-mode") == 0;
        int on = !varmode ?
            newval.i_int : var_GetInteger(vout, "deinterlace");
        char *mode = varmode ?
            newval.psz_string : var_GetString(vout, "deinterlace-mode");
        vouts_osd_Message(&vout, 1, _("Deinterlace %s (%s)"),
                          on == 1 ? _("On") : _("Off"), mode);
        if (!varmode)
            free(mode);
    }

    else if (strcmp(var, "sub-margin") == 0 && newval.i_int != oldval.i_int)
        vouts_osd_Message(&vout, 1, _("Subtitle position %d px"), newval.i_int);

    else if (strcmp(var, "secondary-sub-margin") == 0 && newval.i_int != oldval.i_int)
        vouts_osd_Message(&vout, 1, _("Secondary subtitle position %d px"), newval.i_int);

    else if (strcmp(var, "sub-text-scale") == 0)
        vouts_osd_Message(&vout, 1, _("Subtitle text scale %d%%"), newval.i_int);

    else if (strcmp(var, "zoom") == 0)
    {
        if (newval.f_float == 1.f)
            vouts_osd_Message(&vout, 1, _("Zooming reset"));
        else
        {
            bool found =  vout_osd_PrintVariableText(vout, var, VLC_VAR_FLOAT,
                                                     newval, _("Zoom mode: %s"));
            if (!found)
                vouts_osd_Message(&vout, 1, _("Zoom: x%.2f"), newval.f_float);
        }
    }

    (void) data;
    return VLC_SUCCESS;
}
