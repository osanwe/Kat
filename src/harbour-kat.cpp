/*
  Copyright (C) 2016 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QScopedPointer>

#include <sailfishapp.h>

#include "filesaver.h"
#include "mediaplayerwrapper.h"
#include "settingswrapper.h"
#include "vksdk/src/vksdk.h"

int main(int argc, char *argv[]) {
    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QScopedPointer<FileSaver> fileSaver(new FileSaver(view.data()));
    view->rootContext()->setContextProperty("fileSaver", fileSaver.data());

    QScopedPointer<MediaPlayerWrapper> player(new MediaPlayerWrapper(view.data()));
    view->rootContext()->setContextProperty("player", player.data());

    QScopedPointer<SettingsWrapper> settings(new SettingsWrapper(view.data()));
    view->rootContext()->setContextProperty("settings", settings.data());

    QScopedPointer<VkSDK> vksdk(new VkSDK(view.data()));
    view->rootContext()->setContextProperty("vksdk", vksdk.data());

    view->setSource(SailfishApp::pathTo("qml/harbour-kat.qml"));
    view->show();

    return application->exec();
}

