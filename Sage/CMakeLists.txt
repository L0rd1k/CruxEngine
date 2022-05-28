cmake_minimum_required(VERSION 3.0...3.5)

project(Sage)


set(SOURCES 
    src/Sage/Application.cpp
    src/Sage/Window/Linux/LinuxWindow.cpp
    src/Sage/Layer/Layer.cpp
    src/Sage/Layer/LayerSet.cpp
)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(3rdParty/GLAD)
add_subdirectory(3rdParty/GLFW)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} GL glfw glad)
