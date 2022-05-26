cmake_minimum_required(VERSION 3.0...3.5)

project(Flow)

set(SOURCES 
src/Flow/Application.cpp
src/Flow/Window/Linux/LinuxWindow.cpp
)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory(3rdParty/GLFW)


add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})
