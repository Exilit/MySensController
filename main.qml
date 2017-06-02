import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import de.exilit.mysenscontroller 1.0

ApplicationWindow {
    visible: true
    width: 320
    height: width*1.7
    title: qsTr("MySensor Controller")

    Controller {
        id: controller;
        onConnectionEstablished: mainPage.statusIndicator.active = true;
        onConnectionLost: mainPage.statusIndicator.active = false;
        onSensorAdded: mainPage.addSensor(sensor);
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
            id: mainPage
        }

        Page2 {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Main")
        }
        TabButton {
            text: qsTr("Log")
        }
    }
}
