/*
 * Created by gbian on 03/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// NOLINTBEGIN(*-include-cleaner)
#pragma once
#include "Window.hpp"
#include "FPSCounter.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

class App {
public:
    App();
    ~App();

    App(const App &) = delete;
    App &operator=(const App &) = delete;

    void run();

private:
    /*void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();*/
    void createProgram();
    void createBuffers();

    Window lveWindow{wwidth, wheight, wtile};
    Shader shaderProgram;
    VAO VAO1;
    VBO VBO1;
    EBO EBO1;
};

// NOLINTEND(*-include-cleaner)