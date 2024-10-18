qt_add_qml_module(LxUITestComponent STATIC
    URI LxUI.TestComponent
    VERSION 1.0
    RESOURCE_PREFIX /lastix
    SOURCES
        TestComponent.cpp
        TestComponent.hpp
    DEPENDENCIES
        QtQuick
)

target_link_libraries(LxUITestComponent PRIVATE Qt6::Quick Qt6::Gui)