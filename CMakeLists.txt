cmake_minimum_required(VERSION 3.16)
project(qmlcutieplugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(INSTALL_DIR "$$[QT_INSTALL_QML]/Cutie")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus Gui Qml Quick)
pkg_check_modules(LIBPULSE libpulse REQUIRED IMPORTED_TARGET)

qt_add_qml_module(qmlcutieplugin
    URI qmlcutieplugin
    VERSION ${PROJECT_VERSION}
    PLUGIN_TARGET qmlcutieplugin
)

target_sources(qmlcutieplugin PRIVATE
    src/atmosphere/atmospheremodel.cpp src/atmosphere/atmospheremodel.h
    src/modem/cutiemodem.cpp src/modem/cutiemodem.h
    src/modem/modemsettings.cpp src/modem/modemsettings.h
    src/modem/ofonomodem.cpp src/modem/ofonomodem.h
    src/notifications/notifications.cpp src/notifications/notifications.h
    src/plugin.cpp src/plugin.h
    src/store/cutiestore.cpp src/store/cutiestore.h
    src/volume/cutievolume.cpp src/volume/cutievolume.h
    src/wifi/cutienetworkconnection.cpp src/wifi/cutienetworkconnection.h
    src/wifi/wifiaccesspoint.cpp src/wifi/wifiaccesspoint.h
    src/wifi/wifisettings.cpp src/wifi/wifisettings.h
)

target_include_directories(qmlcutieplugin PUBLIC
    src
)

target_link_libraries(qmlcutieplugin PUBLIC
    Qt::Core
    Qt::DBus
    Qt::Gui
    Qt::Qml
    Qt::Quick
    PkgConfig::LIBPULSE
)

install(TARGETS qmlcutieplugin
    RUNTIME DESTINATION "${INSTALL_DIR}"
    BUNDLE DESTINATION "${INSTALL_DIR}"
    LIBRARY DESTINATION "${INSTALL_DIR}"
)

install(DIRECTORY qml/Cutie DESTINATION "$$[QT_INSTALL_QML]")
