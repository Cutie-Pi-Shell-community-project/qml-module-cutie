import QtQuick
import QtQuick.Controls
import QtQuick.Window
import Cutie

Item {
    height: titleText.height * 3/2 + (description != "" ? descriptionText.height * 3/2 : 0)
    property string title: "Page"
    property string description: ""

    Text {
        id: titleText
        text: title
        anchors.top: parent.top
        anchors.topMargin: height / 2
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        font.pixelSize: 34
        font.family: "Lato"
        font.weight: Font.Bold
        horizontalAlignment: Text.AlignLeft
    	color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    }

    Text {
        id: descriptionText
        text: description
        anchors.top: titleText.bottom
        anchors.topMargin: height / 2
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        font.pixelSize: 15
        font.family: "Lato"
        font.weight: Font.Normal
        horizontalAlignment: Text.AlignLeft
    	color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    }
}