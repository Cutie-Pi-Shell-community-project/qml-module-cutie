TEMPLATE = lib
CONFIG += qt plugin link_pkgconfig
QT += qml quick dbus
PKGCONFIG += libpulse

TARGET  = qmlcutieplugin

SOURCES += src/plugin.cpp \
	src/atmosphere/atmospheremodel.cpp \
	src/wifi/wifisettings.cpp \
	src/wifi/wifiaccesspoint.cpp \
	src/wifi/cutienetworkconnection.cpp \
	src/modem/modemsettings.cpp \
	src/modem/cutiemodem.cpp \
	src/modem/ofonomodem.cpp \
	src/notifications/notifications.cpp \
	src/volume/cutievolume.cpp \
	src/store/cutiestore.cpp

HEADERS += src/plugin.h \
	src/atmosphere/atmospheremodel.h \
	src/wifi/wifisettings.h \
	src/wifi/wifiaccesspoint.h \
	src/wifi/cutienetworkconnection.h \
	src/modem/modemsettings.h \
	src/modem/cutiemodem.h \
	src/modem/ofonomodem.h \
	src/notifications/notifications.h \
	src/volume/cutievolume.h \
	src/store/cutiestore.h

INCLUDEPATH += src

lib.files = qml/Cutie
lib.path = $$[QT_INSTALL_QML]
target.path = $$[QT_INSTALL_QML]/Cutie
INSTALLS += lib target
DBUS_INTERFACES += org.cutie_shell.xml
