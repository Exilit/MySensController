import QtQuick 2.7

Page1Form {
    buttonSearch.onClicked: {
        controller.connectToHost(textHost.text, textPort.text);
    }
}
