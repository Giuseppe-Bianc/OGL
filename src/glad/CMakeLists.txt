include(GenerateExportHeader)

#find_package(glm REQUIRED)
add_library(glad glad.c)

add_library(OGL::glad  ALIAS glad )

# Retrieve the target name
get_target_property(target_name glad  NAME)
include("${CMAKE_SOURCE_DIR}/cmake/Simd.cmake")
set_simd_instructions(${target_name})


#[[target_link_libraries(glad
        PRIVATE
        Vandior_options
        Vandior_warnings
        PUBLIC
        fmt::fmt
        spdlog::spdlog
        #glm::glm
        #nlohmann_json::nlohmann_json
)]]

target_include_directories(glad
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        "${CMAKE_BINARY_DIR}/configured_files/include"
)
if (Vandior_BUILD_FUZZ_TESTS)
    target_link_libraries(glad PRIVATE -fsanitize=fuzzer-no-link)
    target_compile_options(glad PRIVATE -fsanitize=fuzzer-no-link)
endif ()

target_compile_features(glad PUBLIC cxx_std_${CMAKE_CXX_STANDARD})


set_target_properties(
        glad
        PROPERTIES VERSION ${PROJECT_VERSION}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(glad EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/VandiorCore/glad_export.hpp)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(glad PUBLIC VANDIOR_LIB_STATIC_DEFINE)
endif ()
