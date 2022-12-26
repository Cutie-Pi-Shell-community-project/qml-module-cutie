import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import Cutie 1.0

Button {
	id: root
	width: parent.width
	property string subText: ""
	property CutieMenu menu
	padding: 15
	bottomPadding: 10

	onPressAndHold: {
		if (menu) menu.open();
	}

	background: CutieTile {
		anchors.fill: parent
		anchors.topMargin: 5
		anchors.leftMargin: 10
		anchors.rightMargin: 10
		opacity: highlighted || pressed ? 1.0 : 0.0
	}

	contentItem: RowLayout {
		spacing: 15
		anchors.fill: parent
		anchors.leftMargin: 30
		anchors.rightMargin: 30
		anchors.topMargin: 15
		anchors.bottomMargin: 15
		Item {
			width: iconImage.status == Image.Ready ? iconImage.width : 0
			height: width
			Image {
				id: iconImage
				width: 20
				height: width
				source: root.icon.source
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
		}

		ColumnLayout {
        		Layout.fillWidth: true
			Text {
				text: root.text
				font.pixelSize: 15
				font.family: "Lato"
				color: (Atmosphere.variant == "dark") ? "white" : "black"
        			Layout.fillWidth: true
			}
			Text {
				id: subTextItem
				text: root.subText
				visible: root.subText !== ""
				font.pixelSize: 10
				font.family: "Lato"
				color: (Atmosphere.variant == "dark") ? "white" : "black"
        			Layout.fillWidth: true
			}
		}
	}
}