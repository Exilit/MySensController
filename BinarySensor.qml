import QtQuick 2.4

import de.exilit.mysenscontroller 1.0

BinarySensorForm {
    property Sensor sensor;

    switcher.onClicked: {
        sensor.setState(switcher.checked);
    }

    function setSensor(sensor) {
        this.sensor = sensor;
        text = sensor.name;
        switcher.checked = sensor.state;
        console.log("sensor state: ", sensor.state);
        console.log("switcher state: ", switcher.checked);
    }
}
