include(GenerateExportHeader)


find_package(glm REQUIRED)
add_library(ogl_lib_core ogl_lib_core.cpp)

add_library(OGL::ogl_lib_core ALIAS ogl_lib_core)

# Retrieve the target name
get_target_property(target_name ogl_lib_core NAME)
include("${CMAKE_SOURCE_DIR}/cmake/Simd.cmake")
set_simd_instructions(${target_name})


target_link_libraries(ogl_lib_core
        PRIVATE
        OGL_options
        OGL_warnings
        PUBLIC
        fmt::fmt
        spdlog::spdlog
        glm::glm
)

target_include_directories(ogl_lib_core
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        "${CMAKE_BINARY_DIR}/configured_files/include"
)
if (Vandior_BUILD_FUZZ_TESTS)
    target_link_libraries(ogl_lib_core PRIVATE -fsanitize=fuzzer-no-link)
    target_compile_options(ogl_lib_core PRIVATE -fsanitize=fuzzer-no-link)
endif ()

target_compile_features(ogl_lib_core PUBLIC cxx_std_${CMAKE_CXX_STANDARD})


set_target_properties(
        ogl_lib_core
        PROPERTIES VERSION ${PROJECT_VERSION}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(ogl_lib_core EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/OGL/ogl_lib_core_export.hpp)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(ogl_lib_core PUBLIC OGL_LIB_STATIC_DEFINE)
endif ()
