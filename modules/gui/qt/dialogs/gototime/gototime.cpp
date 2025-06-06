/*****************************************************************************
 * gototime.cpp : GotoTime and About dialogs
 ****************************************************************************
 * Copyright (C) 2007 the VideoLAN team
 *
 * Authors: Jean-Baptiste Kempf <jb (at) videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "gototime.hpp"

#include "player/player_controller.hpp"
#include "util/vlctick.hpp"

#include <QLabel>
#include <QTimeEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>

GotoTimeDialog::GotoTimeDialog( qt_intf_t *_p_intf)
               : QVLCDialog( nullptr, _p_intf )
{
    setWindowFlags( Qt::Tool );
    setWindowTitle( qtr( "Go to Time" ) );
    setWindowRole( "vlc-goto-time" );

    QGridLayout *mainLayout = new QGridLayout( this );
    mainLayout->setSizeConstraint( QLayout::SetFixedSize );

    QPushButton *gotoButton = new QPushButton( qtr( "&Go" ) );
    QPushButton *cancelButton = new QPushButton( qtr( "&Cancel" ) );
    QDialogButtonBox *buttonBox = new QDialogButtonBox;

    gotoButton->setDefault( true );
    buttonBox->addButton( gotoButton, QDialogButtonBox::AcceptRole );
    buttonBox->addButton( cancelButton, QDialogButtonBox::RejectRole );

    QLabel *timeIntro = new QLabel( qtr( "Go to time" ) + ":" );
    timeIntro->setWordWrap( true );
    timeIntro->setAlignment( Qt::AlignCenter );

    timeEdit = new QTimeEdit();
    timeEdit->setDisplayFormat( "HH'H':mm'm':ss's'" );
    timeEdit->setAlignment( Qt::AlignRight );
    timeEdit->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );

    QPushButton *resetButton = new QPushButton( QIcon(":/menu/update.svg"), "" );
    resetButton->setToolTip( qtr("Reset") );

    mainLayout->addWidget( timeIntro, 0, 0, 1, 1 );
    mainLayout->addWidget( timeEdit, 0, 1, 1, 1 );
    mainLayout->addWidget( resetButton, 0, 2, 1, 1 );

    mainLayout->addWidget( buttonBox, 1, 0, 1, 3 );

    connect( buttonBox, &QDialogButtonBox::accepted, this, &GotoTimeDialog::accept );
    connect( buttonBox, &QDialogButtonBox::rejected, this, &GotoTimeDialog::reject );

    BUTTONACT( resetButton, &GotoTimeDialog::reset );

    QVLCTools::restoreWidgetPosition( p_intf, "gototimedialog", this );
}

GotoTimeDialog::~GotoTimeDialog()
{
    QVLCTools::saveWidgetPosition( p_intf, "gototimedialog", this );
}

void GotoTimeDialog::toggleVisible()
{
    reset();
    if ( !isVisible() && THEMIM->hasInput() )
    {
        VLCTime time = THEMIM->getTime();
        timeEdit->setTime( timeEdit->time().addSecs( time.toSeconds() ) );
    }
    QVLCDialog::toggleVisible();
    if(isVisible())
        activateWindow();
}

void GotoTimeDialog::reject()
{
    reset();
    QVLCDialog::reject();
}

void GotoTimeDialog::accept()
{
    if ( THEMIM->hasInput() )
    {
        int i_time = QTime( 0, 0, 0 ).msecsTo( timeEdit->time() );
        THEMIM->setTime( VLC_TICK_FROM_MS(i_time) );
    }

    QVLCDialog::accept();
}

void GotoTimeDialog::reset()
{
    timeEdit->setTime( QTime( 0, 0, 0) );
}
