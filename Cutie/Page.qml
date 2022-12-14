import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Window 2.15

Page {
    background: null

    readonly property Item pageContainer: SwipeView.view

    property bool backNavigation: SwipeView.index > 0
    property bool isCurrentItem: SwipeView.isCurrentItem
    property bool isReady: false

    Component.onCompleted: {
        isReady = true;
    }
    
    RadialGradient {
        opacity: (isCurrentItem && backNavigation && isReady) ? 1.0 : 0.0
        width: 25* Screen.pixelDensity
        height: 25* Screen.pixelDensity
        gradient: Gradient {
            GradientStop { position: 0.0; color: (atmospheresHandler.variant == "dark") ? "#ffffff" : "#000000" }
            GradientStop { position: 0.5; color: "transparent" }
        }
        anchors.horizontalCenter: parent.left
        anchors.top: parent.top
        anchors.topMargin: 15* Screen.pixelDensity
        Behavior on opacity {
            NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad; duration: 500 }
        }
    }
}
