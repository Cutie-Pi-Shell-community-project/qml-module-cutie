import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import Cutie 1.0

TextField {
    id: root
    
    color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
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
        color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    }
}


