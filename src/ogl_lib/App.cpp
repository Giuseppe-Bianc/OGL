/*
 * Created by gbian on 03/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#include "OGL/App.hpp"

App::App() {}

App::~App() {}

void App::run() {
    while(!lveWindow.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        lveWindow.swapBuffers();
        glfwPollEvents();
    }
}