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

// Vertices coordinates
GLfloat vertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // Lower left corner
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
    0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Upper right corner
    0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f   // Lower right corner
};

// Indices for vertices order
GLuint indices[] = {
    0, 2, 1,  // Upper triangle
    0, 3, 2   // Lower triangle
};

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
        Window lveWindow{wwidth, wheight, wtile};
        // Generates Shader object using shaders defualt.vert and default.frag
        auto vertp = calculateRelativePathToShaders(curentP, "default.vert");
        auto fragp = calculateRelativePathToShaders(curentP, "default.frag");
        // LINFO("Vertex shader path: {}", fs::canonical(vertp));
        // LINFO("Fragment shader path: {}", fs::canonical(fragp));
        Shader shaderProgram(fs::canonical(vertp).string().c_str(), fs::canonical(fragp).string().c_str());

        // Generates Vertex Array Object and binds it
        VAO VAO1;
        VAO1.Bind();

        // Generates Vertex Buffer Object and links it to vertices
        VBO VBO1(vertices, sizeof(vertices));
        // Generates Element Buffer Object and links it to indices
        EBO EBO1(indices, sizeof(indices));
        // Links VBO to VAO
        VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * TypeSizes::sizeOfFloat, (void *)0);
        VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * TypeSizes::sizeOfFloat, (void *)(3 * TypeSizes::sizeOfFloat));
        VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * TypeSizes::sizeOfFloat, (void *)(6 * TypeSizes::sizeOfFloat));
        // Unbind all to prevent accidentally modifying them
        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
        auto pop_catp = calculateRelativePathToTextures(curentP, "pop_cat.png");
        LINFO("Texture path: {}", fs::canonical(pop_catp));
        // Texture
        Texture popCat(fs::canonical(pop_catp).string().c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        popCat.texUnit(shaderProgram, "tex0", 0);

        // Main while loop
        FPSCounter fpsCounter{lveWindow.getGLFWWindow(), wtile};
        while(!lveWindow.shouldClose()) {
            fpsCounter.frameInTitle(false, false);
            // Specify the color of the background
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            // Clean the back buffer and assign the new color to it
            glClear(GL_COLOR_BUFFER_BIT);
            // Tell OpenGL which Shader Program we want to use
            shaderProgram.Activate();
            glUniform1f(uniID, 0.5f);
            popCat.Bind();
            // Bind the VAO so OpenGL knows to use it
            VAO1.Bind();
            // Draw primitives, number of indices, datatype of indices, index of indices
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // Swap the back buffer with the front buffer
            lveWindow.swapBuffers();
            // Take care of all GLFW events
            glfwPollEvents();
        }

        // Delete all the objects we've created
        VAO1.Delete();
        VBO1.Delete();
        EBO1.Delete();
        popCat.Delete();
        shaderProgram.Delete();
        shaderProgram.Delete();
        return EXIT_SUCCESS;

    } catch(const std::exception &e) { LERROR("Unhandled exception in main: {}", e.what()); }
}

// clang-format off
// NOLINTEND(*-include-cleaner, *-use-anonymous-namespace, *-easily-swappable-parameters, *-implicit-bool-conversion, *-init-variables)
// clang-format on
