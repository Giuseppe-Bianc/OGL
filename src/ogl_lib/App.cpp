/*
 * Created by gbian on 03/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// NOLINTBEGIN(*-include-cleaner)
#include "OGL/App.hpp"
/*
// Vertices coordinates
GLfloat vertices[] = {
    -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower left corner
    0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f,  // Lower right corner
    0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f,  // Inner left
    0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f,  // Inner right
    0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f   // Inner down
};

// Indices for vertices order
GLuint indices[] = {
    0, 3, 5,  // Lower left triangle
    3, 2, 4,  // Upper triangle
    5, 4, 1   // Lower right triangle
};

App::App() {
    createProgram();
    createBuffers();
}

App::~App() {
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
}

void App::run() {
    FPSCounter fpsCounter{lveWindow.getGLFWWindow(), wtile};
    while(!lveWindow.shouldClose()) {
        fpsCounter.frameInTitle(false, false);
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        lveWindow.swapBuffers();
        glfwPollEvents();
    }
}

void App::createProgram() {
    auto vertp = calculateRelativePathToSrcShaders(curentP, "default.vert");
    auto fragp = calculateRelativePathToSrcShaders(curentP, "default.frag");
    LINFO("Vertex shader path: {}", fs::canonical(vertp));
    LINFO("Fragment shader path: {}", fs::canonical(fragp));
    shaderProgram = Shader(fragp.string().c_str(), vertp.string().c_str());
}

void App::createBuffers() {
    VAO1.Bind();
    VBO1 = VBO(vertices, sizeof(vertices));
    EBO1 = EBO(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VBO1.Unbind();
    EBO1.Unbind();
}*/

// NOLINTEND(*-include-cleaner)
