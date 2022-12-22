import QtQuick 2.14
import Cutie 1.0

Item {
    id: root

    signal toggled(value: bool)
    property bool value: false

    height: 20
    width: 40
    Rectangle {
        width: 40
        height: 5
        radius: 0.5 * height
        y: 7.5
        color: (Atmosphere.variant == "dark") ? "#88ffffff" : "#88000000"
    }
    Rectangle {
        width: 20
        height: 20
        radius: 0.5 * height
        y: 0
        x: root.value ? 20 : 0
        color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.value = !root.value
            root.toggled(root.value);
        }
    }
}
