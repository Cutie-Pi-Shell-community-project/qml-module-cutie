cmake_minimum_required(VERSION 3.16)
project(qmlcutieplugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus Gui Qml Quick)
pkg_check_modules(LIBPULSE libpulse REQUIRED IMPORTED_TARGET)
pkg_check_modules(CUTIESTORE cutiestore REQUIRED IMPORTED_TARGET)

qt_standard_project_setup()

set(plugin_SOURCES
    src/atmosphere/atmospheremodel.cpp src/atmosphere/atmospheremodel.h
    src/modem/cutiemodem.cpp src/modem/cutiemodem.h
    src/modem/cutiecall.cpp src/modem/cutiecall.h
    src/modem/modemsettings.cpp src/modem/modemsettings.h
    src/modem/ofonomodem.cpp src/modem/ofonomodem.h
    src/modem/ofonocall.cpp src/modem/ofonocall.h
    src/notifications/notifications.cpp src/notifications/notifications.h
    src/plugin.cpp src/plugin.h
    src/volume/cutievolume.cpp src/volume/cutievolume.h
    src/wifi/cutienetworkconnection.cpp src/wifi/cutienetworkconnection.h
    src/wifi/wifiaccesspoint.cpp src/wifi/wifiaccesspoint.h
    src/wifi/wifisettings.cpp src/wifi/wifisettings.h
    src/mobilenetwork/mobilenetwork.cpp src/mobilenetwork/mobilenetwork.h)

qt6_add_qml_module(qmlcutieplugin
    URI Cutie
    VERSION ${PROJECT_VERSION}
    PLUGIN_TARGET qmlcutieplugin
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        ${plugin_SOURCES}
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
    PkgConfig::CUTIESTORE
)

install(TARGETS qmlcutieplugin
    RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml/Cutie"
    BUNDLE DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml/Cutie"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml/Cutie"
)

install(DIRECTORY qml/Cutie DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml")