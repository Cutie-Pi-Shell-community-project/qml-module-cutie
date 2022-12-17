import QtQuick 2.14
import Cutie 1.0

Rectangle {
    signal clicked()
    property string buttonText: ""

    id: root
    width: buttonText.width + 40
    height: buttonText.height + 10
    radius: 0.5 * root.height
    color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    Text {
        id: buttonText
        text: root.buttonText
		font.pixelSize: 15
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
