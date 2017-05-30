import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 320
    height: width*1.7
    title: qsTr("MySensor Controller")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
//            button1.onClicked: {
//                tabBar.currentIndex = 1;
//                tabBar.currentIndex = swipeView.currentIndex;
//                secondPage.text2.text = "That was easy";
//            }

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
//        TabButton {
//            text: qsTr("Second")
//        }
//        TabButton {
//            text: qsTr("Third")
//        }
    }
}
