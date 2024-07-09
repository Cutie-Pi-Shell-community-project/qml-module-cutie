import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie
import Cutie.Feedback

Button {
    id: root
    property string buttonText
    property alias color: backgroundRect.color
    text: buttonText
    font.pixelSize: 15
    font.family: "Lato"
    height: contentLabel.height + 10
    padding: 5

    onIconChanged: {
        if (icon.name) {
            contentIcon.usingTheme = true;
            contentIcon.source = "image://icon/" + icon.name;
        } else if (icon.source) {
            contentIcon.usingTheme = false;
            contentIcon.source = icon.source;
        }
    }

    onClicked: {
        CutieFeedback.trigger(Application.name, "button-pressed", {}, -1);
    }

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

    contentItem: Column {
        anchors.centerIn: parent

        Row {
            id: contentRow
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height
            spacing: 10

            Image {
                id: contentIcon
                width: 0; height: 0
                visible: !root.icon.color
                property bool usingTheme: false
                anchors.verticalCenter: parent.verticalCenter

                onStatusChanged: {
                    if (status == Image.Error && usingTheme) {
                        usingTheme = false;
                        source = root.icon.source;
                    }

                    if (status == Image.Ready) {
                        height = root.height - 10;
                        width = height * root.icon.width / root.icon.height;
                    }
                }
            }

            ColorOverlay {
                source: contentIcon
                color: root.icon.color
                visible: root.icon.color
                width: Math.min(contentIcon.width, root.icon.height)
                height: Math.min(contentIcon.height, root.icon.width)
                anchors.verticalCenter: parent.verticalCenter
            }

            CutieLabel {
                id: contentLabel
                text: root.text
                font: root.font
                elide: Text.ElideRight
                anchors.verticalCenter: parent.verticalCenter
                visible: root.text != ""
            }
        }
    }
}