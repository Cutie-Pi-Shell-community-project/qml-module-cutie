TEMPLATE = lib
CONFIG += qt plugin
QT += qml quick dbus

TARGET  = qmlcutieplugin

SOURCES += src/plugin.cpp \
	src/atmosphere/atmospheremodel.cpp \
	src/wifi/wifisettings.cpp \
	src/wifi/wifiaccesspoint.cpp \
	src/wifi/cutienetworkconnection.cpp

HEADERS += src/plugin.h \
	src/atmosphere/atmospheremodel.h \
	src/wifi/wifisettings.h \
	src/wifi/wifiaccesspoint.h \
	src/wifi/cutienetworkconnection.h

INCLUDEPATH += src

lib.files = qml/Cutie
lib.path = $$[QT_INSTALL_QML]
target.path = $$[QT_INSTALL_QML]/Cutie
INSTALLS += lib target
DBUS_INTERFACES += org.cutie_shell.xml
