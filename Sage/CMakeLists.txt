cmake_minimum_required(VERSION 3.0...3.5)

project(Sage)

include_directories(.)

set(SOURCES 
    src/sage/application.cpp
    src/sage/window/linux/linux_window.cpp
    src/sage/layer/layer.cpp
    src/sage/layer/layer_set.cpp
)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(3rdParty/GLAD)
add_subdirectory(3rdParty/GLFW)
add_subdirectory(3rdParty/ImGui)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(test_sources 
    ./test/dstructs/iterators/test_random_access_iterator.cpp
    ./test/dstructs/iterators/test_reverse_iterator.cpp
)


foreach(files IN LISTS test_sources)
    get_filename_component(filename ${files} NAME_WE)
    add_executable(${filename})
    target_sources(${filename} PRIVATE ${files})
    target_link_libraries(${filename} PRIVATE
        gtest_main
    )
    add_test(NAME ${filename} COMMAND ${filename})
endforeach()

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} GL glfw glad ImGui)
