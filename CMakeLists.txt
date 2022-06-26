cmake_minimum_required(VERSION 3.0...3.5)

project(SageEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

#> Sage engine supported options
option(USE_IMGUI "Enable ImGui library support support" ON)
option(USE_GTEST "Enable google test support" OFF)

#> Sage engine definitions
if (USE_IMGUI)
  add_definitions(-USE_IMGUI)
endif()
if (USE_GTEST)
  add_definitions(-USE_GTEST)
endif()

add_subdirectory(Sage)
add_subdirectory(Sandbox)



