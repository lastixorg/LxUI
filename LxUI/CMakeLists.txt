add_subdirectory(Slider)
add_subdirectory(TestComponent)
add_subdirectory(Theme)

add_library(LxUI INTERFACE)
target_link_libraries(LxUI INTERFACE LxUISliderplugin LxUITestComponentplugin LxUIThemeplugin)

target_include_directories(LxUI INTERFACE ${PROJECT_SOURCE_DIR})

