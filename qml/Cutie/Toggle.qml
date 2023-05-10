import QtQuick
import QtQuick.Controls
import Cutie

Switch {
    id: root
    leftPadding: 10
    rightPadding: 10
    topPadding: 5
    bottomPadding: 5
    height: 40
    width: 75

    background: Rectangle {
        anchors.centerIn: parent
        height: 3
        width: root.availableWidth - root.rightPadding - root.leftPadding
        radius: height / 2
        color: (Atmosphere.variant == "dark") ? "#8fffffff" : "#60000000"
    }

    indicator: Rectangle {
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + 5
        width: 20
        height: 20
        radius: width / 2
        color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"

        Behavior on x {
            NumberAnimation { duration: 100 }
        }
    }

}