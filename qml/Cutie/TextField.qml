import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie

TextField {
    id: root
    
    color: Atmosphere.textColor
    clip: true
    font.family: "Lato"
    font.pixelSize: 15 
    padding: 10
    background: Rectangle {
        id: backgroundRect
        anchors.bottom: parent.bottom
        height: 3
        x: 5
        width: parent.width - 10
        radius: 2
        color: parent.focus ? Atmosphere.accentColor : Atmosphere.textColor
    }
}