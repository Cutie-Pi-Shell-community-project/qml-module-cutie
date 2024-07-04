import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie

ListView {
    id: root
	property CutieMenu menu
    property string floatIconName
    property url floatIconSource
    signal floatAction()
    footerPositioning: ListView.OverlayFooter
    footer: Item {
        height: visible ? 100 : 0
        width: root.width
        visible: !!menu || floatIconName
            || floatIconSource.toString()
        z: 100
        CutieButton {
            width: 50
            height: 50
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 25
            icon.name: menu ? "open-menu-symbolic" : floatIconName
            icon.source: floatIconSource
            icon.color: Atmosphere.textColor
            property bool usingTheme: false

            onClicked: {
                root.floatAction();
                if (menu) {
                    menu.y = root.height - menu.height - 100
                    menu.open();
                }
            }
        }
    }
}


