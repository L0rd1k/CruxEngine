cmake_minimum_required(VERSION 3.0...3.5)

project(Sandbox)
include_directories(../Crux)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Crux)

