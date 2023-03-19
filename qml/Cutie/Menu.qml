import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie

Menu {
	id: root
	x: 20
	y: parent.height + 10
	width: parent.width - 40
	modal: true
	dim: false
	topPadding: 5
	bottomPadding: 10

	background: Rectangle {
		id: backgroundRect
		anchors.fill: parent
		radius: 5
		color: Atmosphere.primaryColor
	}

	enter: Transition {
		NumberAnimation { 
			property: "opacity"
			duration: 100
			from: 0.0
			to: 1.0 
		}
	}

	exit: Transition {
		NumberAnimation { 
			property: "opacity"
			duration: 100
			from: 1.0
			to: 0.0 
		}
	}
}