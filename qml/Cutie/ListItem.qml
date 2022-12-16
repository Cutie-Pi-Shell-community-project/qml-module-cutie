import Cutie 1.0
import QtQuick 2.14
import QtGraphicalEffects 1.15
import Cutie 1.0

Item {
	id: root
	height: 35 + (subText != "" ? 15 : 0)
	width: parent.width
	property var text: ""
	property var subText: ""
	property var icon: ""
	signal clicked()
	CutieTile {
		x: 15
		y: 2
		width: mouse.pressed ? parent.width - 2 * x : 0
		height: parent.height - 2 * y
		opacity: mouse.pressed ? 1.0 : 0.0

		Behavior on width {
			NumberAnimation { duration: 200 }
		}
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
		font.pixelSize: 15
		font.family: "Lato"
		color: (Atmosphere.variant == "dark") ? "white" : "black"
	}


	Text {
		x: 20 + (root.icon ? iconImage.width + iconImage.x : 0)
		y: 30
		text: root.subText
		font.pixelSize: 10
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