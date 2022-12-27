import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import Cutie 1.0

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
		color: (Atmosphere.variant == "dark") ? "#ffffff" : "#000000"
	}
}