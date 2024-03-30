import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Cutie

Button {
	id: root
	width: parent.width
	property string subText: ""
	property bool iconOverlay: true
	property CutieMenu menu
	padding: 15
	bottomPadding: 10

    onIconChanged: {
        if (icon.name) {
            iconImage.usingTheme = true;
            iconImage.source = "image://icon/" + icon.name;
        } else if (icon.source) {
            iconImage.usingTheme = false;
            iconImage.source = icon.source;
        }
    }


	onPressAndHold: {
		if (menu) {
        	CutieFeedback.trigger(Application.name, "button-pressed", {}, -1);
			menu.open();
		}
	}

    onClicked: {
        CutieFeedback.trigger(Application.name, "button-pressed", {}, -1);
    }

	background: CutieTile {
		anchors.fill: parent
		anchors.topMargin: 5
		anchors.leftMargin: 10
		anchors.rightMargin: 10
		opacity: highlighted || pressed ? 1.0 : 0.0
	}

	contentItem: RowLayout {
		spacing: iconImage.status == Image.Ready ? 15 : 0
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.leftMargin: 20
		anchors.rightMargin: 30
		height: Math.max(iconItem.height, textCol.height)
		Item {
			id: iconItem
			width: iconImage.status == Image.Ready ? iconImage.width : 0
			height: iconImage.status == Image.Ready ? iconImage.height : 0
			Image {
				id: iconImage
				width: root.icon.width
				height: root.icon.height
				source: root.icon.source
				fillMode: Image.PreserveAspectFit
				sourceSize.width: width
				sourceSize.height: height
				visible: !colorOverlay.visible
                property bool usingTheme: false

                onStatusChanged: {
                    if (status == Image.Error && usingTheme) {
                        usingTheme = false;
                        source = root.icon.source;
                    }

                    if (status == Image.Ready) {
                        height = root.height - 10;
                        width = height * root.icon.width / root.icon.height;
                    }
                }
			}

			ColorOverlay {
				id: colorOverlay
                source: iconImage
                color: root.icon.color ? root.icon.color : Atmosphere.textColor
                visible: root.icon.color || root.iconOverlay
                width: Math.min(iconImage.width, root.icon.height)
                height: Math.min(iconImage.height, root.icon.width)
                anchors.verticalCenter: parent.verticalCenter
			}
		}

		ColumnLayout {
			id: textCol
        	Layout.fillWidth: true
			spacing: subTextItem.visible ? 5 : 0
			CutieLabel {
				id: mainTextItem
				text: root.text
				font.pixelSize: 15
        		Layout.fillWidth: true
				wrapMode: Text.Wrap
			}
			CutieLabel {
				id: subTextItem
				text: root.subText
				visible: root.subText !== ""
				font.pixelSize: 10
        		Layout.fillWidth: true
				wrapMode: Text.Wrap
			}
		}
	}
}