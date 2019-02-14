cmake_minimum_required(VERSION 3.13)
project(window)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(SFML 2 COMPONENTS graphics audio network window system REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(lib/imgui)

set(
        IMGUI

        lib/imgui/imconfig.h
        lib/imgui/imconfig-SFML.h
        lib/imgui/imgui.h
        lib/imgui/imgui.cpp
        lib/imgui/imgui-SFML.h
        lib/imgui/imgui-SFML.cpp
        lib/imgui/imgui_internal.h
        lib/imgui/imstb_rectpack.h
        lib/imgui/imstb_textedit.h
        lib/imgui/imstb_truetype.h
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_widgets.cpp
)

add_library(imgui ${IMGUI})

add_executable(window main.cpp)
target_link_libraries(window ${SFML_LIBRARIES} imgui ${OPENGL_LIBRARIES})