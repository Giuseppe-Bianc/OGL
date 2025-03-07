/*
 * Created by gbian on 03/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "headers.hpp"
#include <string>
#include <string_view>

static void errorCallback(int error, const char *description);
static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// static void framebufferResizeCallback(GLFWwindow *window, int width, int height) noexcept;
class Window {  // NOLINT(*-special-member-functions)
public:
    Window(const int w, const int h, const std::string_view &window_name) noexcept;
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    [[nodiscard]] GLFWwindow *getGLFWWindow() const noexcept { return window; }
    [[nodiscard]] bool shouldClose() const noexcept { return glfwWindowShouldClose(window); }
    //[[nodiscard]] bool wasWindowResized() noexcept { return framebufferResized; }
    void resetWindowResizedFlag() noexcept { framebufferResized = false; }
    void swapBuffers() const noexcept { glfwSwapBuffers(window); }

    static void initializeGLFW();

private:
    void initWindow();

    void createWindow();

    void setHints() const;

    [[nodiscard]] std::string formatMode(const GLFWvidmode *mode) const;

    void centerWindow();

    int width;
    int height;
    bool framebufferResized = false;
    std::string_view windowName;
    GLFWwindow *window{nullptr};
};
