import QtQuick 2.15
import QtQuick.Controls 2.15
import Cutie 1.0

Slider {
    id: root

    leftPadding: 10
    rightPadding: 10
    topPadding: 5
    bottomPadding: 5
    height: 40

    background: Rectangle {
        x: 25
        y: 19
        height: 2
        width: root.availableWidth - root.rightPadding - root.leftPadding
        radius: height / 2
        color: (Atmosphere.variant == "dark") ? "#8fffffff" : "#60000000"
    }

    handle: Rectangle {
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding
        width: 30
        height: 30
        radius: width / 2
        color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    }

}