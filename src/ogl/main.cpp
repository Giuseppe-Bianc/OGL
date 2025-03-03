// clang-format off
// NOLINTBEGIN(*-include-cleaner, *-use-anonymous-namespace, *-easily-swappable-parameters, *-implicit-bool-conversion, *-init-variables)
// clang-format on
#include <array>
#include <functional>
#include <iostream>
#include <optional>

#include <random>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

#include "OGL/ogl_lib.hpp"

// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, const char **argv) {
    INIT_LOG()
    try {
        CLI::App app{fmt::format("{} version {}", OGL::cmake::project_name, OGL::cmake::project_version)};
        bool show_version = false;
        app.add_flag("--version", show_version, "Show version information");

        CLI11_PARSE(app, argc, argv);

        if(show_version) {
            fmt::print("{}\n", OGL::cmake::project_version);
            return EXIT_SUCCESS;
        }
        LINFO("{}", glfwGetVersionString());
        App rapp;
        rapp.run();
        return EXIT_SUCCESS;

    } catch(const std::exception &e) { spdlog::error("Unhandled exception in main: {}", e.what()); }
}

// clang-format off
// NOLINTEND(*-include-cleaner, *-use-anonymous-namespace, *-easily-swappable-parameters, *-implicit-bool-conversion, *-init-variables)
// clang-format on
