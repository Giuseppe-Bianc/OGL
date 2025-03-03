add_executable(ogl main.cpp)

get_target_property(target_name ogl NAME)
include("${CMAKE_SOURCE_DIR}/cmake/Simd.cmake")
set_simd_instructions(${target_name})

target_link_libraries(
        ogl
        PRIVATE OGL::OGL_options
        OGL::OGL_warnings)

target_link_system_libraries(
        ogl
        PRIVATE
        CLI11::CLI11
        OGL::ogl_lib)

target_include_directories(ogl PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
