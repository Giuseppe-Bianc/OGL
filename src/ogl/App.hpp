/*
* Created by gbian on 03/03/2025.
* Copyright (c) 2025 All rights reserved.
*/

#pragma once
#include "Window.hpp"

class App {
public:
    App();
    ~App();

    App(const App &) = delete;
    App &operator=(const App &) = delete;

    void run();

private:
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();

    Window lveWindow{640, 480, "Hello World"};
};