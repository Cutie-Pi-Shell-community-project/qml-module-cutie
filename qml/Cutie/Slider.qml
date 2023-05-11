import QtQuick
import QtQuick.Controls
import Cutie

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
        height: 3
        width: root.availableWidth - root.rightPadding - root.leftPadding
        radius: height / 2
        color: Atmosphere.textColor
    }

    handle: Rectangle {
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + 5
        width: 20
        height: 20
        radius: width / 2
        color: Atmosphere.textColor
    }

}