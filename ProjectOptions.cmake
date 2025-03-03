include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(OGL_supports_sanitizers)
    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
        set(SUPPORTS_UBSAN ON)
    else ()
        set(SUPPORTS_UBSAN OFF)
    endif ()

    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
        set(SUPPORTS_ASAN OFF)
    else ()
        set(SUPPORTS_ASAN ON)
    endif ()
endmacro()

macro(OGL_setup_options)
    option(OGL_ENABLE_HARDENING "Enable hardening" ON)
    option(OGL_ENABLE_COVERAGE "Enable coverage reporting" OFF)
    cmake_dependent_option(
            OGL_ENABLE_GLOBAL_HARDENING
            "Attempt to push hardening options to built dependencies"
            ON
            OGL_ENABLE_HARDENING
            OFF)

    OGL_supports_sanitizers()

    if (NOT PROJECT_IS_TOP_LEVEL OR OGL_PACKAGING_MAINTAINER_MODE)
        option(OGL_ENABLE_IPO "Enable IPO/LTO" OFF)
        option(OGL_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
        option(OGL_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
        option(OGL_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
        option(OGL_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
        option(OGL_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
        option(OGL_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
        option(OGL_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
        option(OGL_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
        option(OGL_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
        option(OGL_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
        option(OGL_ENABLE_PCH "Enable precompiled headers" OFF)
        option(OGL_ENABLE_CACHE "Enable ccache" OFF)
    else ()
        option(OGL_ENABLE_IPO "Enable IPO/LTO" ON)
        option(OGL_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
        option(OGL_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
        option(OGL_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
        option(OGL_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
        option(OGL_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
        option(OGL_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
        option(OGL_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
        option(OGL_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
        option(OGL_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
        option(OGL_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
        option(OGL_ENABLE_PCH "Enable precompiled headers" OFF)
        option(OGL_ENABLE_CACHE "Enable ccache" ON)
    endif ()

    if (NOT PROJECT_IS_TOP_LEVEL)
        mark_as_advanced(
                OGL_ENABLE_IPO
                OGL_WARNINGS_AS_ERRORS
                OGL_ENABLE_USER_LINKER
                OGL_ENABLE_SANITIZER_ADDRESS
                OGL_ENABLE_SANITIZER_LEAK
                OGL_ENABLE_SANITIZER_UNDEFINED
                OGL_ENABLE_SANITIZER_THREAD
                OGL_ENABLE_SANITIZER_MEMORY
                OGL_ENABLE_UNITY_BUILD
                OGL_ENABLE_CLANG_TIDY
                OGL_ENABLE_CPPCHECK
                OGL_ENABLE_COVERAGE
                OGL_ENABLE_PCH
                OGL_ENABLE_CACHE)
    endif ()

    OGL_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
    if (LIBFUZZER_SUPPORTED AND (OGL_ENABLE_SANITIZER_ADDRESS OR OGL_ENABLE_SANITIZER_THREAD OR OGL_ENABLE_SANITIZER_UNDEFINED))
        set(DEFAULT_FUZZER ON)
    else ()
        set(DEFAULT_FUZZER OFF)
    endif ()

    option(OGL_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(OGL_global_options)
    include(cmake/Simd.cmake)
    check_all_simd_features()
    print_simd_support()
    if (OGL_ENABLE_IPO)
        include(cmake/InterproceduralOptimization.cmake)
        OGL_enable_ipo()
    endif ()

    OGL_supports_sanitizers()

    if (OGL_ENABLE_HARDENING AND OGL_ENABLE_GLOBAL_HARDENING)
        include(cmake/Hardening.cmake)
        if (NOT SUPPORTS_UBSAN
                OR OGL_ENABLE_SANITIZER_UNDEFINED
                OR OGL_ENABLE_SANITIZER_ADDRESS
                OR OGL_ENABLE_SANITIZER_THREAD
                OR OGL_ENABLE_SANITIZER_LEAK)
            set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
        else ()
            set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
        endif ()
        message("${OGL_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${OGL_ENABLE_SANITIZER_UNDEFINED}")
        OGL_enable_hardening(OGL_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
    endif ()
endmacro()

macro(OGL_local_options)
    if (PROJECT_IS_TOP_LEVEL)
        include(cmake/StandardProjectSettings.cmake)
    endif ()

    add_library(OGL_warnings INTERFACE)
    add_library(OGL_options INTERFACE)

    include(cmake/CompilerWarnings.cmake)
    OGL_set_project_warnings(
            OGL_warnings
            ${OGL_WARNINGS_AS_ERRORS}
            ""
            ""
            ""
            "")

    if (OGL_ENABLE_USER_LINKER)
        include(cmake/Linker.cmake)
        OGL_configure_linker(OGL_options)
    endif ()

    include(cmake/Sanitizers.cmake)
    OGL_enable_sanitizers(
            OGL_options
            ${OGL_ENABLE_SANITIZER_ADDRESS}
            ${OGL_ENABLE_SANITIZER_LEAK}
            ${OGL_ENABLE_SANITIZER_UNDEFINED}
            ${OGL_ENABLE_SANITIZER_THREAD}
            ${OGL_ENABLE_SANITIZER_MEMORY})

    set_target_properties(OGL_options PROPERTIES UNITY_BUILD ${OGL_ENABLE_UNITY_BUILD})

    if (OGL_ENABLE_PCH)
        target_precompile_headers(
                OGL_options
                INTERFACE
                <vector>
                <string>
                <utility>)
    endif ()

    if (OGL_ENABLE_CACHE)
        include(cmake/Cache.cmake)
        OGL_enable_cache()
    endif ()

    include(cmake/StaticAnalyzers.cmake)
    if (OGL_ENABLE_CLANG_TIDY)
        OGL_enable_clang_tidy(OGL_options ${OGL_WARNINGS_AS_ERRORS})
    endif ()

    if (OGL_ENABLE_CPPCHECK)
        OGL_enable_cppcheck(${OGL_WARNINGS_AS_ERRORS} "" # override cppcheck options
        )
    endif ()

    if (OGL_ENABLE_COVERAGE)
        include(cmake/Tests.cmake)
        OGL_enable_coverage(OGL_options)
    endif ()

    if (OGL_WARNINGS_AS_ERRORS)
        check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
        if (LINKER_FATAL_WARNINGS)
            # This is not working consistently, so disabling for now
            # target_link_options(OGL_options INTERFACE -Wl,--fatal-warnings)
        endif ()
    endif ()

    if (OGL_ENABLE_HARDENING AND NOT OGL_ENABLE_GLOBAL_HARDENING)
        include(cmake/Hardening.cmake)
        if (NOT SUPPORTS_UBSAN
                OR OGL_ENABLE_SANITIZER_UNDEFINED
                OR OGL_ENABLE_SANITIZER_ADDRESS
                OR OGL_ENABLE_SANITIZER_THREAD
                OR OGL_ENABLE_SANITIZER_LEAK)
            set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
        else ()
            set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
        endif ()
        OGL_enable_hardening(OGL_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
    endif ()

endmacro()
