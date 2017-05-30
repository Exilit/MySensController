import QtQuick 2.7

import de.exilit.mysenscontroller 1.0

Page1Form {
    Controller {
        id: controller
    }

    buttonSearch.onClicked: {
        controller.connectToHost(textHost.text, textPort.text);
    }
}
