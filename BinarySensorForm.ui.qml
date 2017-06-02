import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

Rectangle {
    property alias text: label.text
    property alias checked: switcher.checked

    Layout.fillWidth: true
    height: 25
    color: "transparent"
    property alias switcher: switcher

    Label {
        id: label
        text: qsTr("Label")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Switch {
        id: switcher
        anchors.verticalCenterOffset: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: label.verticalCenter
        checked: false
    }
}
