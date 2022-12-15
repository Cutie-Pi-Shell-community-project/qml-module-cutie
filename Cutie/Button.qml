import QtQuick 2.14
import Cutie 1.0

Rectangle {
    signal clicked()
    property string buttonText: ""

    id: root
    width: buttonText.width + 50
    height: buttonText.height + 20
    radius: 0.5 * root.height
    color: (Atmosphere.variant == "dark") ? "#CCffffff" : "#80000000"
    Text {
        id: buttonText
        text: root.buttonText
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        color: (Atmosphere.variant == "dark") ? "#000000" : "#ffffff"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked();
        }
    }
}
