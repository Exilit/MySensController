import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Qt.labs.settings 1.0

Item {
    id: item1
    width: 320
    property alias buttonSearch: buttonSearch
    property alias textHost: textHost
    property alias textPort: textPort

//    property regex validIpAddressRegex: /^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/
//    property QRegExp validHostnameRegex: /^(([a-zA-Z]|[a-zA-Z][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z]|[A-Za-z][A-Za-z0-9\-]*[A-Za-z0-9])$/;

    ColumnLayout {
        id: columnLayout
        anchors.rightMargin: 10
        anchors.bottomMargin: 380
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent

        TextField {
            id: textHost
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            placeholderText: qsTr("Host")
            validator: RegExpValidator{regExp: /(^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$)|(^(([a-zA-Z]|[a-zA-Z][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z]|[A-Za-z][A-Za-z0-9\-]*[A-Za-z0-9])$)/}
        }

        TextField {
            id: textPort
            text: "5003"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            placeholderText: qsTr("Port")
            validator: IntValidator{bottom: 0; top: 65536}
        }

        Button {
            id: buttonSearch
            text: qsTr("Search")
            Layout.fillWidth: true
        }
    }

    Settings {
        id: settings
        property alias host: textHost.text
        property alias port: textPort.text
    }
}
