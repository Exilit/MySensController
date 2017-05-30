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
        id: controller
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

//        Page2 {
//            id: secondPage;
//        }

//        Page {
//            Label {
//                text: qsTr("Second page")
//                anchors.centerIn: parent
//            }
//        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
    }
}
