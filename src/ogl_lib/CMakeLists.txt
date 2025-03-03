include(GenerateExportHeader)


add_library(ogl_lib ogl_lib.cpp)


add_library(OGL::ogl_lib ALIAS ogl_lib)

target_link_libraries(ogl_lib PRIVATE OGL_options OGL_warnings)

target_include_directories(ogl_lib ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(ogl_lib PUBLIC cxx_std_20)

set_target_properties(
        ogl_lib
        PROPERTIES VERSION ${PROJECT_VERSION}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(ogl_lib EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/OGL/ogl_lib_export.hpp)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(ogl_lib PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif ()
