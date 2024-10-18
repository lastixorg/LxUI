add_subdirectory(Slider)
add_subdirectory(TestComponent)

add_library(LxUI INTERFACE)
target_link_libraries(LxUI INTERFACE LxUISliderplugin LxUITestComponentplugin)
