###############################################################################
# Automake targets and declarations
###############################################################################

AUTOMAKE_OPTIONS = subdir-objects

###############################################################################
# Unit/regression test
###############################################################################
noinst_PROGRAMS =
check_PROGRAMS = \
	test_libvlc_core \
	test_libvlc_equalizer \
	test_libvlc_media \
	test_libvlc_media_callback \
	test_libvlc_media_thumbnail_argb \
	test_libvlc_media_thumbnail_jpeg \
	test_libvlc_media_thumbnail_png \
	test_libvlc_media_thumbnail_webp \
	test_libvlc_media_list \
	test_libvlc_media_player \
	test_libvlc_media_player_record \
	test_libvlc_media_discoverer \
	test_libvlc_renderer_discoverer \
	test_libvlc_slaves \
	test_src_config_chain \
	test_src_clock_clock \
	test_src_clock_start \
	test_src_misc_ancillary \
	test_src_misc_variables \
	test_src_input_stream \
	test_src_input_stream_fifo \
	test_src_preparser_thumbnail \
	test_src_preparser_thumbnail_to_files \
	test_src_input_decoder \
	test_src_player \
	test_src_player_monotonic_clock \
	test_src_interface_dialog \
	test_src_media_source \
	test_src_misc_bits \
	test_src_misc_chroma_probe \
	test_src_misc_epg \
	test_src_misc_keystore \
	test_src_misc_image \
	test_src_misc_viewpoint \
	test_src_video_output \
	test_src_video_output_opengl \
	test_modules_lua_extension \
	test_modules_misc_medialibrary \
	test_modules_packetizer_helpers \
	test_modules_packetizer_hxxx \
	test_modules_packetizer_h264 \
	test_modules_packetizer_hevc \
	test_modules_packetizer_mpegvideo \
	test_modules_codec_hxxx_helper \
	test_modules_keystore \
	test_modules_demux_timestamps \
	test_modules_demux_timestamps_filter \
	test_modules_demux_ts_pes \
	test_modules_playlist_m3u \
	test_modules_stream_out_pcr_sync \
	test_modules_tls \
	test_modules_stream_out_transcode \
	test_modules_mux_webvtt \
	test_modules_stream_out_hls_subtitles_segmenter \
	$(NULL)

if HAVE_GL
check_PROGRAMS += \
	test_modules_video_output_opengl_filters \
	test_modules_video_output_opengl_sub_renderer
endif

if HAVE_GLES2
check_PROGRAMS += \
	test_modules_video_output_opengl_es2_filters \
	test_modules_video_output_opengl_es2_sub_renderer
endif

if HAVE_DARWIN
check_PROGRAMS += test_src_misc_image_cvpx
endif


if UPDATE_CHECK
check_PROGRAMS += test_src_crypto_update
endif
if HAVE_TAGLIB
check_PROGRAMS += test_libvlc_meta
endif

check_SCRIPTS = \
	modules/lua/telnet.sh \
	check_POTFILES.sh

# Disabled tests:
EXTRA_PROGRAMS = \
	test_libvlc_media_list_player \
	test_src_input_stream_net \
	$(NULL)

EXTRA_DIST = \
	modules/lua/extensions/extensions.lua \
	samples/certs/certkey.pem \
	samples/empty.voc \
	samples/image.jpg \
	samples/meta.mp3 \
	samples/subitems \
	samples/slaves \
	$(check_SCRIPTS)

check_HEADERS = libvlc/test.h libvlc/libvlc_additions.h libvlc/media_utils.h \
	libvlc/media_player.h

TESTS = $(check_PROGRAMS) check_POTFILES.sh

AM_CPPFLAGS = \
	-DSRCDIR=\"$(srcdir)\" \
	-DTOP_BUILDDIR=\"$(abs_top_builddir)\" \
	-DTOP_SRCDIR=\"$(abs_top_srcdir)\"

if HAVE_EMSCRIPTEN
AM_CFLAGS = -sMAIN_MODULE=1
endif

AM_LDFLAGS = -no-install $(LDFLAGS_vlc)
LIBVLCCORE = -L../src/ -lvlccore
LIBVLC = -L../lib -lvlc

test_libvlc_core_SOURCES = libvlc/core.c
test_libvlc_core_LDADD = $(LIBVLC)
test_libvlc_equalizer_SOURCES = libvlc/equalizer.c
test_libvlc_equalizer_LDADD = $(LIBVLC)
test_libvlc_media_SOURCES = libvlc/media.c
test_libvlc_media_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_callback_SOURCES = libvlc/media_callback.c
test_libvlc_media_callback_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_thumbnail_argb_SOURCES = libvlc/media_thumbnail.c
test_libvlc_media_thumbnail_argb_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_thumbnail_argb_CPPFLAGS = $(AM_CPPFLAGS) -DTEST_THUMB_TYPE=libvlc_picture_Argb -DTEST_REQUIRED_MODULES=\"avcodec\"
test_libvlc_media_thumbnail_png_SOURCES = libvlc/media_thumbnail.c
test_libvlc_media_thumbnail_png_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_thumbnail_png_CPPFLAGS = $(AM_CPPFLAGS) -DTEST_THUMB_TYPE=libvlc_picture_Png -DTEST_REQUIRED_MODULES=\"png\"
test_libvlc_media_thumbnail_jpeg_SOURCES = libvlc/media_thumbnail.c
test_libvlc_media_thumbnail_jpeg_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_thumbnail_jpeg_CPPFLAGS = $(AM_CPPFLAGS) -DTEST_THUMB_TYPE=libvlc_picture_Jpg -DTEST_REQUIRED_MODULES=\"jpeg\"
test_libvlc_media_thumbnail_webp_SOURCES = libvlc/media_thumbnail.c
test_libvlc_media_thumbnail_webp_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_thumbnail_webp_CPPFLAGS = $(AM_CPPFLAGS) -DTEST_THUMB_TYPE=libvlc_picture_WebP -DTEST_REQUIRED_MODULES=\"vpx\"
test_libvlc_media_list_player_SOURCES = libvlc/media_list_player.c
test_libvlc_media_list_player_LDADD = $(LIBVLC)
test_libvlc_media_list_SOURCES = libvlc/media_list.c
test_libvlc_media_list_LDADD = $(LIBVLC)
test_libvlc_media_player_SOURCES = libvlc/media_player.c
test_libvlc_media_player_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_player_record_SOURCES = libvlc/media_player_record.c
test_libvlc_media_player_record_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_media_discoverer_SOURCES = libvlc/media_discoverer.c
test_libvlc_media_discoverer_LDADD = $(LIBVLC)
test_libvlc_renderer_discoverer_SOURCES = libvlc/renderer_discoverer.c
test_libvlc_renderer_discoverer_LDADD = $(LIBVLC)
test_libvlc_slaves_SOURCES = libvlc/slaves.c
test_libvlc_slaves_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_libvlc_meta_SOURCES = libvlc/meta.c
test_libvlc_meta_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_src_clock_clock_SOURCES = src/clock/clock.c \
	../src/clock/clock.c \
	../src/clock/clock_internal.c
test_src_clock_clock_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_clock_start_SOURCES = src/clock/clock_start.c \
	../src/clock/clock.c \
	../src/clock/clock_internal.c
test_src_clock_start_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_src_misc_ancillary_SOURCES = src/misc/ancillary.c
test_src_misc_ancillary_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_misc_variables_SOURCES = src/misc/variables.c
test_src_misc_variables_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_config_chain_SOURCES = src/config/chain.c
test_src_config_chain_LDADD = $(LIBVLCCORE)
test_src_crypto_update_SOURCES = src/crypto/update.c
test_src_crypto_update_LDADD = $(LIBVLCCORE) $(GCRYPT_LIBS)
test_src_input_stream_SOURCES = src/input/stream.c
test_src_input_stream_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_input_stream_net_SOURCES = src/input/stream.c
test_src_input_stream_net_CFLAGS = $(AM_CFLAGS) -DTEST_NET
test_src_input_stream_net_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_input_stream_fifo_SOURCES = src/input/stream_fifo.c
test_src_input_stream_fifo_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_preparser_thumbnail_SOURCES = src/preparser/thumbnail.c
test_src_preparser_thumbnail_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_preparser_thumbnail_to_files_SOURCES = src/preparser/thumbnail_to_files.c
test_src_preparser_thumbnail_to_files_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_player_SOURCES = src/player/player.c
test_src_player_LDADD = $(LIBVLCCORE) $(LIBVLC) $(LIBM)
test_src_player_monotonic_clock_SOURCES = src/player/player.c
test_src_player_monotonic_clock_CFLAGS = $(AM_CFLAGS) -DTEST_CLOCK_MONOTONIC
test_src_player_monotonic_clock_LDADD = $(LIBVLCCORE) $(LIBVLC) $(LIBM)
test_src_misc_bits_SOURCES = src/misc/bits.c
test_src_misc_bits_LDADD = $(LIBVLC)
test_src_misc_epg_SOURCES = src/misc/epg.c
test_src_misc_epg_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_misc_keystore_SOURCES = src/misc/keystore.c
test_src_misc_keystore_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_misc_image_cvpx_SOURCES = src/misc/image_cvpx.c
test_src_misc_image_cvpx_LDADD = $(LIBVLCCORE) $(LIBVLC) ../modules/libvlc_vtutils.la
test_src_misc_image_cvpx_LDFLAGS = $(AM_LDFLAGS) -Wl,-framework,CoreVideo
test_src_misc_viewpoint_SOURCES = src/misc/viewpoint.c
test_src_misc_viewpoint_LDADD = $(LIBVLCCORE) $(LIBM)
test_src_interface_dialog_SOURCES = src/interface/dialog.c
test_src_interface_dialog_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_media_source_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_media_source_SOURCES = src/media_source/media_source.c

test_src_video_output_SOURCES = \
	src/video_output/video_output.c \
	src/video_output/video_output.h \
	src/video_output/video_output_scenarios.c
test_src_video_output_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_src_video_output_opengl_SOURCES = src/video_output/opengl.c
test_src_video_output_opengl_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_src_input_decoder_SOURCES = \
	src/input/decoder/input_decoder.c \
	src/input/decoder/input_decoder.h \
	src/input/decoder/input_decoder_scenarios.c
test_src_input_decoder_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_src_misc_chroma_probe_SOURCES = src/misc/chroma_probe.c
test_src_misc_chroma_probe_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_src_misc_image_SOURCES = src/misc/image.c
test_src_misc_image_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_modules_lua_extension_SOURCES = modules/lua/extension.c
test_modules_lua_extension_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_lua_extension_CPPFLAGS = $(AM_CPPFLAGS)
test_modules_misc_medialibrary_SOURCES = modules/misc/medialibrary.c
test_modules_misc_medialibrary_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_packetizer_helpers_SOURCES = modules/packetizer/helpers.c
test_modules_packetizer_helpers_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_packetizer_hxxx_SOURCES = modules/packetizer/hxxx.c
test_modules_packetizer_hxxx_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_packetizer_h264_SOURCES = modules/packetizer/h264.c \
				modules/packetizer/packetizer.h
test_modules_packetizer_h264_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_packetizer_hevc_SOURCES = modules/packetizer/hevc.c \
				modules/packetizer/packetizer.h
test_modules_packetizer_hevc_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_packetizer_mpegvideo_SOURCES = modules/packetizer/mpegvideo.c \
				modules/packetizer/packetizer.h
test_modules_packetizer_mpegvideo_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_keystore_SOURCES = modules/keystore/test.c
test_modules_keystore_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_tls_SOURCES = modules/misc/tls.c
test_modules_tls_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_demux_timestamps_SOURCES = modules/demux/timestamps.c
test_modules_demux_timestamps_filter_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_demux_timestamps_filter_SOURCES = modules/demux/timestamps_filter.c
test_modules_demux_ts_pes_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_demux_ts_pes_SOURCES = modules/demux/ts_pes.c \
				../modules/demux/mpeg/ts_pes.c \
				../modules/demux/mpeg/ts_pes.h
test_modules_playlist_m3u_SOURCES = modules/demux/playlist/m3u.c
test_modules_playlist_m3u_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_modules_codec_hxxx_helper_SOURCES = modules/codec/hxxx_helper.c \
                                      ../modules/codec/hxxx_helper.c \
                                      ../modules/packetizer/hxxx_nal.c \
                                      ../modules/packetizer/h264_slice.c \
                                      ../modules/packetizer/h264_nal.c \
                                      ../modules/packetizer/hevc_nal.c
test_modules_codec_hxxx_helper_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_video_output_opengl_filters_SOURCES = \
	modules/video_output/opengl/filters.c \
	../modules/video_output/opengl/filters.c \
	../modules/video_output/opengl/filters.h \
	../modules/video_output/opengl/filter.c \
	../modules/video_output/opengl/gl_api.c \
	../modules/video_output/opengl/gl_api.h \
	../modules/video_output/opengl/interop.c \
	../modules/video_output/opengl/interop.h \
	../modules/video_output/opengl/importer.c \
	../modules/video_output/opengl/importer.h
test_modules_video_output_opengl_filters_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_video_output_opengl_filters_CPPFLAGS = $(AM_CPPFLAGS) -DVLC_TEST_OPENGL_API=VLC_OPENGL
test_modules_video_output_opengl_es2_filters_SOURCES = $(test_modules_video_output_opengl_filters_SOURCES)
test_modules_video_output_opengl_es2_filters_LDADD = $(LIBVLCCORE) $(LIBVLC)
test_modules_video_output_opengl_es2_filters_CPPFLAGS = $(AM_CPPFLAGS) -DVLC_TEST_OPENGL_API=VLC_OPENGL_ES2

test_modules_video_output_opengl_sub_renderer_SOURCES = \
	modules/video_output/opengl/sub_renderer.c \
	../modules/video_output/opengl/sub_renderer.c \
	../modules/video_output/opengl/sub_renderer.h \
	../modules/video_output/opengl/filter.c \
	../modules/video_output/opengl/gl_api.c \
	../modules/video_output/opengl/gl_api.h \
	../modules/video_output/opengl/gl_util.c \
	../modules/video_output/opengl/gl_util.h \
	../modules/video_output/opengl/interop.c \
	../modules/video_output/opengl/interop.h
test_modules_video_output_opengl_sub_renderer_LDADD = $(LIBVLCCORE) $(LIBVLC) $(LIBPLACEBO_LIBS)
test_modules_video_output_opengl_sub_renderer_CPPFLAGS = $(AM_CPPFLAGS) -DVLC_TEST_OPENGL_API=VLC_OPENGL
test_modules_video_output_opengl_es2_sub_renderer_SOURCES = $(test_modules_video_output_opengl_sub_renderer_SOURCES)
test_modules_video_output_opengl_es2_sub_renderer_LDADD = $(LIBVLCCORE) $(LIBVLC) $(LIBPLACEBO_LIBS)
test_modules_video_output_opengl_es2_sub_renderer_CPPFLAGS = $(AM_CPPFLAGS) -DVLC_TEST_OPENGL_API=VLC_OPENGL_ES2

test_modules_stream_out_transcode_SOURCES = \
	modules/stream_out/transcode.c \
	modules/stream_out/transcode.h \
	modules/stream_out/transcode_scenarios.c
test_modules_stream_out_transcode_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_modules_stream_out_pcr_sync_SOURCES = modules/stream_out/pcr_sync.c \
	../modules/stream_out/transcode/pcr_sync.c \
	../modules/stream_out/transcode/pcr_sync.h \
	../modules/stream_out/transcode/pcr_helper.h \
	../modules/stream_out/transcode/pcr_helper.c
test_modules_stream_out_pcr_sync_LDADD = $(LIBVLCCORE)

test_modules_mux_webvtt_SOURCES = modules/mux/webvtt.c
test_modules_mux_webvtt_LDADD = $(LIBVLCCORE) $(LIBVLC)

test_modules_stream_out_hls_subtitles_segmenter_SOURCES = \
	modules/stream_out/hls/subtitles_segmenter.c \
	../modules/stream_out/hls/hls.h \
	../modules/stream_out/hls/subtitles_segmenter.c
test_modules_stream_out_hls_subtitles_segmenter_LDADD = $(LIBVLCCORE) $(LIBVLC)

checkall:
	$(MAKE) check_PROGRAMS="$(check_PROGRAMS) $(EXTRA_PROGRAMS)" check

FORCE:
	@echo "Generated source cannot be phony. Go away." >&2
	@exit 1

.PHONY: FORCE

libvlc_demux_run_la_SOURCES = src/input/demux-run.c src/input/demux-run.h \
	src/input/common.c src/input/common.h $(top_srcdir)/src/input/var.c
libvlc_demux_run_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/src
libvlc_demux_run_la_LDFLAGS = -no-install -static
libvlc_demux_run_la_LIBADD = \
	../lib/libvlc.la ../src/libvlccore.la ../compat/libcompat.la
if !HAVE_DYNAMIC_PLUGINS
libvlc_demux_run_la_CPPFLAGS += -DHAVE_STATIC_MODULES
libvlc_demux_run_la_LIBADD += \
	../modules/libxml_plugin.la \
	../modules/libconsole_logger_plugin.la \
	../modules/libaiff_plugin.la \
	../modules/libasf_plugin.la \
	../modules/libau_plugin.la \
	../modules/libavi_plugin.la \
	../modules/libcaf_plugin.la \
	../modules/libdemux_cdg_plugin.la \
	../modules/libes_plugin.la \
	../modules/libflacsys_plugin.la \
	../modules/libh26x_plugin.la \
	../modules/libmjpeg_plugin.la \
	../modules/libmp4_plugin.la \
	../modules/libnsv_plugin.la \
	../modules/libnuv_plugin.la \
	../modules/libps_plugin.la \
	../modules/libpva_plugin.la \
	../modules/libsap_plugin.la \
	../modules/libsmf_plugin.la \
	../modules/libsubtitle_plugin.la \
	../modules/libtta_plugin.la \
	../modules/libttml_plugin.la \
	../modules/libty_plugin.la \
	../modules/libvoc_plugin.la \
	../modules/libwav_plugin.la \
	../modules/libwebvtt_plugin.la \
	../modules/libxa_plugin.la \
	../modules/libpacketizer_a52_plugin.la \
	../modules/libpacketizer_copy_plugin.la \
	../modules/libpacketizer_dts_plugin.la \
	../modules/libpacketizer_flac_plugin.la \
	../modules/libpacketizer_h264_plugin.la \
	../modules/libpacketizer_hevc_plugin.la \
	../modules/libpacketizer_mlp_plugin.la \
	../modules/libpacketizer_mpeg4audio_plugin.la \
	../modules/libpacketizer_mpeg4video_plugin.la \
	../modules/libpacketizer_mpegaudio_plugin.la \
	../modules/libpacketizer_mpegvideo_plugin.la \
	../modules/libpacketizer_vc1_plugin.la \
	../modules/librawaud_plugin.la \
	../modules/librawvid_plugin.la \
	../modules/libfilesystem_plugin.la \
	../modules/libxml_plugin.la \
	../modules/libogg_plugin.la \
	-lstdc++
if HAVE_DVBPSI
libvlc_demux_run_la_CPPFLAGS += -DHAVE_DVBPSI
libvlc_demux_run_la_LIBADD += ../modules/libts_plugin.la
endif
if HAVE_MATROSKA
libvlc_demux_run_la_CPPFLAGS += -DHAVE_MATROSKA
libvlc_demux_run_la_LIBADD += ../modules/libmkv_plugin.la
endif
endif
EXTRA_LTLIBRARIES = libvlc_demux_run.la

libvlc_demux_dec_run_la_SOURCES = $(libvlc_demux_run_la_SOURCES) \
	src/input/decoder.c src/input/decoder.h
libvlc_demux_dec_run_la_CPPFLAGS = $(libvlc_demux_run_la_CPPFLAGS) -DHAVE_DECODERS
libvlc_demux_dec_run_la_LDFLAGS = $(libvlc_demux_run_la_LDFLAGS)
libvlc_demux_dec_run_la_LIBADD = $(libvlc_demux_run_la_LIBADD)
if !HAVE_DYNAMIC_PLUGINS
libvlc_demux_dec_run_la_LIBADD += \
	../modules/libadpcm_plugin.la \
	../modules/libaes3_plugin.la \
	../modules/libaraw_plugin.la \
	../modules/libg711_plugin.la \
	../modules/liblpcm_plugin.la \
	../modules/libuleaddvaudio_plugin.la \
	../modules/librawvideo_plugin.la \
	../modules/libcc_plugin.la \
	../modules/libcvdsub_plugin.la \
	../modules/libdvbsub_plugin.la \
	../modules/libscte18_plugin.la \
	../modules/libscte27_plugin.la \
	../modules/libspudec_plugin.la \
	../modules/libstl_plugin.la \
	../modules/libsubsdec_plugin.la \
	../modules/libsubsusf_plugin.la \
	../modules/libsvcdsub_plugin.la \
	../modules/libtextst_plugin.la \
	../modules/libsubstx3g_plugin.la
endif
if HAVE_ZVBI
libvlc_demux_dec_run_la_LIBADD += ../modules/libzvbi_plugin.la
endif
if HAVE_TELX
libvlc_demux_dec_run_la_LIBADD += ../modules/libtelx_plugin.la
endif
EXTRA_LTLIBRARIES += libvlc_demux_dec_run.la

#
# Fuzzers
#
vlc_demux_run_LDFLAGS = -no-install -static
vlc_demux_run_LDADD = libvlc_demux_run.la
vlc_demux_dec_run_SOURCES = vlc-demux-run.c
vlc_demux_dec_run_LDFLAGS = -no-install -static
vlc_demux_dec_run_LDADD = libvlc_demux_dec_run.la
EXTRA_PROGRAMS += vlc-demux-run vlc-demux-dec-run

vlc_demux_libfuzzer_LDADD = libvlc_demux_run.la
vlc_demux_dec_libfuzzer_SOURCES = vlc-demux-libfuzzer.c
vlc_demux_dec_libfuzzer_LDADD = libvlc_demux_dec_run.la
if HAVE_LIBFUZZER
noinst_PROGRAMS += vlc-demux-libfuzzer vlc-demux-dec-libfuzzer vlc-demux-run vlc-demux-dec-run
endif

vlccoreios_SOURCES = iosvlc.m
vlccoreios_LDFLAGS = $(LDFLAGS_vlc) -Wl,-framework,Foundation,-framework,UIKit
vlccoreios_LDFLAGS += -Xlinker -rpath -Xlinker "@executable_path/Frameworks/"
vlccoreios_OBJCFLAGS = -fobjc-arc
vlccoreios_LDADD = ../lib/libvlc.la ../src/libvlccore.la
if HAVE_IOS
noinst_PROGRAMS += vlccoreios
endif

if HAVE_TVOS
noinst_PROGRAMS += vlccoreios
endif

if HAVE_XROS
noinst_PROGRAMS += vlccoreios
endif

vlccorewatchos_SOURCES = watchosvlc.m
vlccorewatchos_LDFLAGS = $(LDFLAGS_vlc) -Wl,-framework,WatchKit
vlccorewatchos_LDFLAGS += -Xlinker -rpath -Xlinker "@executable_path/Frameworks/"
vlccorewatchos_OBJCFLAGS = -fobjc-arc
vlccorewatchos_LDADD = ../lib/libvlc.la ../src/libvlccore.la

if HAVE_WATCHOS
noinst_PROGRAMS += vlccorewatchos
endif

vlc_window_SOURCES = vlc-window.c
vlc_window_CPPFLAGS = $(AM_CPPFLAGS) -I../include/
vlc_window_LDADD = ../lib/libvlc.la ../src/libvlccore.la ../compat/libcompat.la
# Opt-out for building the test driver if there is no dynamic plugins, since we
# cannot link static plugins currently anyway.
if HAVE_DYNAMIC_PLUGINS
noinst_PROGRAMS += vlc-window
endif
