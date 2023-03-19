import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie

Button {
    id: root
    property string buttonText
    property alias color: backgroundRect.color
    text: buttonText
    font.pixelSize: 15
    font.family: "Lato"
    padding: 10
    background: Rectangle {
        id: backgroundRect
        anchors.fill: parent
        radius: 5
        color: Atmosphere.primaryColor
        Rectangle {
            anchors.fill: parent
            radius: 5
            color: Atmosphere.secondaryColor
            opacity: root.pressed || root.checked ? .75 : 0
        }
    }
    contentItem: Label {
        text: root.text
        font: root.font
        color: Atmosphere.textColor
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
    }
}