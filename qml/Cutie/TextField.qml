import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import Cutie 1.0

TextField {
    id: root
    
    color: (Atmosphere.variant == "dark") ? "#000000" : "#ffffff"
    clip: true
    font.family: "Lato"
    font.pixelSize: 15 
    padding: 10
    background: Rectangle {
        id: backgroundRect
        anchors.fill: parent
		radius: 8 
        color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    }
}


