TEMPLATE = lib
CONFIG += qt plugin
QT += qml quick dbus

DESTDIR = Cutie
TARGET  = qmlcutieplugin

SOURCES += plugin.cpp \
	atmospheremodel.cpp \
	wifisettings.cpp

HEADERS += plugin.h \
	atmospheremodel.h \
	wifisettings.h

lib.files = Cutie
lib.path = $$[QT_INSTALL_QML]
target.path = $$[QT_INSTALL_QML]/Cutie
INSTALLS += lib target
DBUS_INTERFACES += org.cutie_shell.xml
