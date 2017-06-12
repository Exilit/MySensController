import QtQuick 2.7

Page1Form {
    function addSensor(sensor) {
        var comp = Qt.createComponent("BinarySensor.qml");
        var binSensor = comp.createObject(columnLayout, {"sensor": sensor});
//        binSensor.setSensor(sensor);
    }

    buttonSearch.onClicked: {
        controller.connectToHost(textHost.text, textPort.text);
    }
}
