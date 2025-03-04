include(GenerateExportHeader)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
add_library(ogl_lib ogl_lib.cpp
        ../../include/OGL/headers.hpp
        Window.cpp
        ../../include/OGL/Window.hpp
        App.cpp
        ../../include/OGL/App.hpp
        FPSCounter.cpp
        ../../include/OGL/FPSCounter.hpp
        Shader.cpp
        ../../include/OGL/Shader.hpp
        VBO.cpp
        ../../include/OGL/VBO.hpp
        VAO.cpp
        ../../include/OGL/VAO.hpp
        EBO.cpp
        ../../include/OGL/EBO.hpp
        ../../include/OGL/Texture.cpp
        ../../include/OGL/Texture.hpp
)

add_library(OGL::ogl_lib ALIAS ogl_lib)

# Retrieve the target name
get_target_property(target_name ogl_lib NAME)
include("${CMAKE_SOURCE_DIR}/cmake/Simd.cmake")
set_simd_instructions(${target_name})


target_link_libraries(ogl_lib
        PRIVATE
        OGL_options
        OGL_warnings
        PUBLIC
        OGL::ogl_lib_core
        OGL::stb
        OGL::glad
        OpenGL::GL
        glfw
)

target_include_directories(ogl_lib
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        "${CMAKE_BINARY_DIR}/configured_files/include"
)
if (Vandior_BUILD_FUZZ_TESTS)
    target_link_libraries(ogl_lib PRIVATE -fsanitize=fuzzer-no-link)
    target_compile_options(ogl_lib PRIVATE -fsanitize=fuzzer-no-link)
endif ()

target_compile_features(ogl_lib PUBLIC cxx_std_${CMAKE_CXX_STANDARD})


set_target_properties(
        ogl_lib
        PROPERTIES VERSION ${PROJECT_VERSION}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(ogl_lib EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/OGL/ogl_lib_export.hpp)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(ogl_lib PUBLIC OGL_LIB_STATIC_DEFINE)
endif ()
