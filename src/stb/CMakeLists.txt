include(GenerateExportHeader)

add_library(stb stb_image.cpp)

add_library(OGL::stb ALIAS stb)

# Retrieve the target name
get_target_property(target_name stb NAME)
include("${CMAKE_SOURCE_DIR}/cmake/Simd.cmake")
set_simd_instructions(${target_name})



target_include_directories(stb
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        "${CMAKE_BINARY_DIR}/configured_files/include"
)
if (Vandior_BUILD_FUZZ_TESTS)
    target_link_libraries(stb PRIVATE -fsanitize=fuzzer-no-link)
    target_compile_options(stb PRIVATE -fsanitize=fuzzer-no-link)
endif ()

target_compile_features(stb PUBLIC cxx_std_${CMAKE_CXX_STANDARD})


set_target_properties(
        stb
        PROPERTIES VERSION ${PROJECT_VERSION}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(stb EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/OGL/stb_export.hpp)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(stb PUBLIC OGL_LIB_STATIC_DEFINE)
endif ()
