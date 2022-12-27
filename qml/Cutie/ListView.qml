import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import Cutie 1.0

ListView {
    id: root
	property CutieMenu menu
    footerPositioning: ListView.OverlayFooter
    footer: Item {
        height: 100
        width: root.width
        visible: !!menu
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


