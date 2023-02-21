import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie

ListView {
    id: root
	property CutieMenu menu
    footerPositioning: ListView.OverlayFooter
    footer: Item {
        height: !!menu ? 100 : 0
        width: root.width
        visible: !!menu
        z: 100
        CutieButton {
            width: 50
            height: 50
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 25
            text: "\u2261"
            font.pixelSize: 30

            onClicked: {
                if (menu) {
                    menu.y = root.height - menu.height - 100
                    menu.open();
                }
            }
        }
    }
}


