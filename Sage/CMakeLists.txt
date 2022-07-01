cmake_minimum_required(VERSION 3.0...3.5)

project(Sage)

include_directories(.)

add_subdirectory(3rdParty/GLAD)
add_subdirectory(3rdParty/GLFW)
add_subdirectory(3rdParty/GLM)

set(SOURCES
    src/sage/application.cpp
    src/sage/window/linux/linux_window.cpp
    src/sage/layer/layer.cpp
    src/sage/layer/layer_set.cpp
    src/sage/gui/gui_layer.cpp
    src/sage/inputs/linux/linux_input.cpp
    
    src/sage/render/shader.cpp
    src/sage/render/buffer_layout.cpp
    src/sage/render/renderer.cpp
    src/sage/render/renderer_api.cpp
    src/sage/render/render_cmd.cpp

    src/sage/render/opengl/opengl_renderer_context.cpp
    src/sage/render/opengl/opengl_index_buffer.cpp
    src/sage/render/opengl/opengl_vertex_buffer.cpp
    src/sage/render/opengl/opengl_vertex_array.cpp
    src/sage/render/opengl/opengl_renderer_api.cpp
)

if(USE_IMGUI)
    list(APPEND SOURCES
        ./3rdParty/ImGui/imconfig.h
        ./3rdParty/ImGui/imgui_demo.cpp
        ./3rdParty/ImGui/imgui_draw.cpp
        ./3rdParty/ImGui/imgui_tables.cpp
        ./3rdParty/ImGui/backends/imgui_impl_glfw.cpp
        ./3rdParty/ImGui/backends/imgui_impl_glfw.h
        ./3rdParty/ImGui/backends/imgui_impl_opengl3.cpp
        ./3rdParty/ImGui/backends/imgui_impl_opengl3.h
        ./3rdParty/ImGui/imgui_internal.h
        ./3rdParty/ImGui/imgui_widgets.cpp
        ./3rdParty/ImGui/imgui.cpp
        ./3rdParty/ImGui/imgui.h
        ./3rdParty/ImGui/imstb_rectpack.h
        ./3rdParty/ImGui/imstb_textedit.h
        ./3rdParty/ImGui/imstb_truetype.h
    )
endif()

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")

if(USE_GTEST)
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
        ./test/dstructs/test_vector.cpp
        ./test/dstructs/test_array.cpp
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
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} GL glfw glad glm)
