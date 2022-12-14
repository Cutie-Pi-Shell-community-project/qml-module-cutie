import QtQuick 2.14
import QtQuick.Window 2.14
import Cutie 1.0

Window {
    visible: true
    color: "transparent"

    property Item initialPage: null
    readonly property CutiePageStack pageStack: _pageStack

    Component.onCompleted: {
        _pageStack.push(initialPage)
    }

    property Atmosphere atmospheresHandler: atmospheresHandler
    Atmosphere {
        id: atmospheresHandler
    }

    property CutieToastHandler toastHandler: toastHandler
    CutieToastHandler {
        id: toastHandler
    }

    CutiePageStack {
        id: _pageStack
	anchors.fill: parent
    }
}