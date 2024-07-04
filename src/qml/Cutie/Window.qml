import QtQuick
import QtQuick.Window
import Cutie

Window {
    visible: true
    color: "transparent"

    property Item initialPage: null
    readonly property CutiePageStack pageStack: _pageStack

    Component.onCompleted: {
        _pageStack.push(initialPage)
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