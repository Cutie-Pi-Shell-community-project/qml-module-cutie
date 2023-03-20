import QtQuick
import QtQuick.Controls
import Cutie

SwipeView {
    id: _stackView
    anchors.fill: parent

    Timer {
        id: removeTimer
        interval: 500
        repeat: false
        onTriggered: {
            while (currentIndex < count - 1) {
                takeItem(count - 1).destroy();
            }
        }
    }
    
    onCurrentIndexChanged: {
        removeTimer.start();
    }

    function removeTop() {
        while (currentIndex < count - 1) {
            takeItem(currentIndex + 1);
            removeTimer.start();
        }
    }

    readonly property Item currentPage: currentItem
    readonly property int depth: count
    
    function clear() { contentChildren.clear() }
    function push(page, properties) {
        if (!properties) properties = {}
        if (page instanceof Item) {
            for (p in properties) {
                page[p] = properties[p];
            }
            addItem(page);
        } else if (page instanceof Component) { 
            if (page.status == Component.Ready) {
                addItem(page.createObject(_stackView, properties));
            } else page.statusChanged.connect(() => {
                finishBaking(page, properties)
            });
        } else if (typeof page === 'string' || page instanceof String) { 
            let component = Qt.createComponent(page);
            if (component.status == Component.Ready) {
                addItem(component.createObject(_stackView, properties));
            } else component.statusChanged.connect(() => {
                finishBaking(component, properties)
            });
        }
        currentIndex = count - 1;
    }

    function replaceTop(page, properties) {
        takeItem(count - 1).destroy();
        push(page, properties);
    }

    function finishBaking(page, properties) {
        if (page.status == Component.Ready)
            addItem(page.createObject(_stackView, properties));
        currentIndex = count - 1;
    }

    function pop(page) {
        if (page) {
            let i = 0;
	        for (; itemAt(i) !== page; i++);
            currentIndex = i - 1;
        } else {
            currentIndex = count - 2;
        }
    }
}
