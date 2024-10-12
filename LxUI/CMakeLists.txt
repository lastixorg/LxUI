qt_add_library(LxUILib STATIC)


target_link_libraries(LxUILib PRIVATE Qt6::Quick Qt6::Gui)

list(APPEND MODULE_QML_FILES
    Slider/Slider.qml)


target_include_directories(LxUILib PRIVATE TestComponent)

qt_add_qml_module(LxUILib
    URI LxUI
    VERSION 1.0
    RESOURCE_PREFIX /lastix
    QML_FILES
        ${MODULE_QML_FILES}
    SOURCES      
        TestComponent/TestComponent.cpp
        TestComponent/TestComponent.hpp
    DEPENDENCIES
        QtQuick
)

