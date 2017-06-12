import QtQuick 2.4

import de.exilit.mysenscontroller 1.0

BinarySensorForm {
    property BinarySensor sensor;

    text: sensor.name;
    checked: sensor.state;

    switcher.onClicked: {
        sensor.setState(switcher.checked);
    }
}
