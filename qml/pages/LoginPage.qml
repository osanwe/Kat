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

import QtQuick 2.0
import Sailfish.Silica 1.0
import org.nemomobile.notifications 1.0

Page {
    id: loginPage

    Notification {
        id: loginNotification
        category: "harbour-kat"
    }

    SilicaWebView {
        id: loginWebView

        anchors.fill: parent
        url: authorization.buildAuthUrl()

        onUrlChanged: authorization.tryToGetAccessToken(url)
    }

    Connections {
        target: authorization
        onAuthorized: {
            vksdk.setAccessTocken(accessToken)
            vksdk.setUserId(userId)
            settings.setAccessToken(accessToken)
            settings.setUserId(userId)
            pageStack.replace(Qt.resolvedUrl("MainMenuPage.qml"))
            loginNotification.previewBody = qsTr("Logged to vk.com")
            loginNotification.publish()
        }
        onError: {
            loginNotification.previewBody = errorMessage
            loginNotification.publish()
            loginWebView.url = authorization.buildAuthUrl()
        }
    }
}

