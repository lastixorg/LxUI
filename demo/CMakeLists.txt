
qt_add_executable(demo
    main.cpp
)

qt_add_qml_module(demo
    URI demoApp
    VERSION 1.0
    RESOURCE_PREFIX /lastix
    QML_FILES main.qml
    RESOURCES Audiowide-Regular.ttf
)

set_target_properties(demo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER lastix.ui.demo
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(demo
    PRIVATE Qt6::Gui Qt6::Quick LxUI)

install(TARGETS demo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})