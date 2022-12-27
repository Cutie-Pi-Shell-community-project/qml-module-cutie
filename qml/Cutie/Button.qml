import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import Cutie 1.0

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
        color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
        Rectangle {
            anchors.fill: parent
            radius: 5
            color: (Atmosphere.variant == "dark") ? "#000000" : "#ffffff"
            opacity: root.pressed || root.checked ? .25 : 0
        }
    }
    contentItem: Label {
        text: root.text
        font: root.font
        color: (Atmosphere.variant == "dark") ? "#000000" : "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
    }
}


