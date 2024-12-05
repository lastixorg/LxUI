qt_add_qml_module(LxUITheme STATIC
    URI LxUI.Theme
    VERSION 1.0
    RESOURCE_PREFIX /lastix
    SOURCES 
        Theme.cpp 
        Theme.hpp
        Defaults.cpp
    DEPENDENCIES
        QtGui
        QtQuick
        QtCore
)


target_link_libraries(LxUITheme PRIVATE Qt6::Quick Qt6::Gui)