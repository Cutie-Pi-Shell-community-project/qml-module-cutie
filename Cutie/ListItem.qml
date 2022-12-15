import Cutie 1.0
import QtQuick 2.14
import QtGraphicalEffects 1.15
import Cutie 1.0

Item {
	id: root
	height: 30
	width: parent.width
	property var text: ""
	property var icon: ""
	signal clicked()
	CutieTile {
		x: 15
		y: 2
		width: mouse.pressed ? parent.width - 2 * x : 0.0
		height: parent.height - 2 * y
		opacity: mouse.pressed ? 1.0 : 0.0
	}

	Image {
		id: iconImage
		x: 20
		y: 2
		width: 20
		height: width
		source: root.icon
		anchors.verticalCenter: parent.verticalCenter
		fillMode: Image.PreserveAspectFit
		sourceSize.width: width
		sourceSize.height: height
		visible: false
	}

	ColorOverlay {
		anchors.fill: iconImage
		source: iconImage
		color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
	}

	Text {
		x: 20 + (root.icon ? iconImage.width + iconImage.x : 0)
		y: 10
		text: root.text
		font.pixelSize: 14
		font.family: "Lato"
		color: (Atmosphere.variant == "dark") ? "white" : "black"
	}

	MouseArea {
		id: mouse
		anchors.fill: parent
		onClicked: {
			root.clicked()
		}
	}
}