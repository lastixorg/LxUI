qt_add_qml_module(LxUISlider STATIC
    URI LxUI.Slider
    VERSION 1.0
    RESOURCE_PREFIX /lastix
    QML_FILES
        Slider.qml
)

target_link_libraries(LxUISlider PRIVATE Qt6::Quick Qt6::Gui)