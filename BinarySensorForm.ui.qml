import QtQuick 2.4
import QtQuick.Controls 2.1

Item {
    property alias text: label.text
    property alias checked: switcher.checked

    id: rectangle
    height: childrenRect.height + 5

    Switch {
        id: switcher
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: label.verticalCenter
        checked: false
    }

    Label {
        id: label
        text: qsTr("Label")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
    }
}
