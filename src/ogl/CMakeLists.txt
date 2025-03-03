add_executable(ogl main.cpp
        App.cpp
        App.hpp
        Window.cpp
        Window.hpp)

find_package(OpenGL REQUIRED)

target_link_libraries(
        ogl
        PRIVATE OGL::OGL_options
        OGL::OGL_warnings)

target_link_system_libraries(
        ogl
        PRIVATE
        CLI11::CLI11
        fmt::fmt
        spdlog::spdlog
        glm::glm
        OGL::glad
        OpenGL::GL
        glfw)

target_include_directories(ogl PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
