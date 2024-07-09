import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie
import Cutie.Feedback

MenuItem {
	id: root
	width: parent.width
	padding: 15
	bottomPadding: 10

    onTriggered: {
        CutieFeedback.trigger(Application.name, "button-pressed", {}, -1);
    }

	background: CutieTile {
		anchors.fill: parent
		anchors.topMargin: 5
		anchors.leftMargin: 10
		anchors.rightMargin: 10
		opacity: highlighted || pressed ? 1.0 : 0.0
		color: Atmosphere.secondaryColor
	}

	contentItem: RowLayout {
		spacing: 15
		anchors.fill: parent
		anchors.leftMargin: 30
		anchors.rightMargin: 30
		anchors.topMargin: 15
		anchors.bottomMargin: 15
		Item {
			width: iconImage.status == Image.Ready ? 20 : 0
			height: width
			Image {
				id: iconImage
				anchors.fill: parent
				source: root.icon.source
				fillMode: Image.PreserveAspectFit
				sourceSize.width: parent.width
				sourceSize.height: parent.height
				visible: false
			}

			ColorOverlay {
				anchors.fill: iconImage
				source: iconImage
				color: Atmosphere.textColor
			}
		}

		ColumnLayout {
        		Layout.fillWidth: true
			Text {
				text: root.text
				font.pixelSize: 15
				font.family: "Lato"
				color: Atmosphere.textColor
        			Layout.fillWidth: true
			}
		}
	}
}