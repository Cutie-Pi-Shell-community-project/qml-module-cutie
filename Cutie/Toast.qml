import QtQuick 2.14
import Cutie 1.0


Rectangle {
    property real fadingTime: 300
    function show(text, duration) {
        toastText.text = text;
        if(typeof duration !== "undefined" ) {
            fadingTime = duration;
        }
        animation.start();
    }

    id: toastBody
    width: toastText.width + 20
    height: toastText.height + 10
    radius: 15
    opacity: 0
    color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
    anchors {
        horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: toastText
        text: ""
        color: (Atmosphere.variant == "dark") ? "#000000" : "#ffffff"
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }

    SequentialAnimation on opacity {
        id: animation
        running: false

        NumberAnimation {
            to: .9
            duration: fadingTime / 10
        }

        PauseAnimation {
            duration: fadingTime
        }

        NumberAnimation {
            to: 0
            duration: fadingTime / 10
        }
    }
}
