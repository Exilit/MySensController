import QtQuick 2.4

Item {
    id: item1
    width: 400
    height: 400

    ListView {
        id: listView
        anchors.fill: parent
        delegate: Rectangle {
            height: 15
            Text { text: modelData }
        }
        model: controller.messageLog
    }
}
