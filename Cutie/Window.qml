import QtQuick 2.14
import QtQuick.Window 2.14
import Cutie 1.0

Window {
    visible: true
    color: "transparent"

    property Atmosphere atmospheresHandler: atmospheresHandler
    Atmosphere {
        id: atmospheresHandler
    }

    property CutieToastHandler toastHandler: toastHandler
    CutieToastHandler {
        id: toastHandler
    }
}