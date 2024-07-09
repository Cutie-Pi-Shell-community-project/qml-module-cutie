cmake_minimum_required(VERSION 3.16)
project(qmlcutieplugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Qml Quick)
pkg_check_modules(CUTIESTORE cutiestore REQUIRED IMPORTED_TARGET)
pkg_check_modules(ATMOSPHERE atmosphere REQUIRED IMPORTED_TARGET)
pkg_check_modules(CUTIEMODEM cutiemodem REQUIRED IMPORTED_TARGET)
pkg_check_modules(FEEDBACK cutiefeedback REQUIRED IMPORTED_TARGET)

qt_standard_project_setup()

set(plugin_SOURCES
    src/plugin.cpp src/plugin.h
    src/iconprovider.cpp src/iconprovider.h)

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
    Qt::Gui
    Qt::Qml
    Qt::Quick
    PkgConfig::CUTIESTORE
    PkgConfig::ATMOSPHERE
    PkgConfig::CUTIEMODEM
    PkgConfig::FEEDBACK
)

install(TARGETS qmlcutieplugin
    RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml/Cutie"
    BUNDLE DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml/Cutie"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml/Cutie"
)

install(DIRECTORY src/qml/Cutie DESTINATION "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml")