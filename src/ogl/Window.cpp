/*
 * Created by gbian on 03/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#include "Window.hpp"

#include "spdlog/spdlog.h"

#include <stdexcept>
[[nodiscard]] static constexpr auto calcolaCentro(const int &width, const int &w) noexcept { return (width - w) / 2; }
#define CALC_CENTRO(width, w) calcolaCentro(width, w)

void errorCallback(int error, const char *description) { spdlog::info("GLFW Error ({0}): {1}", error, description); }

void keyCallback(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
    switch(key) {  // NOLINT(*-multiway-paths-covered)
    case GLFW_KEY_ESCAPE:
        if(action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            spdlog::info("Escape key pressed, closing window.");
        }
        break;
    [[likely]] default:
        // Handle other keys here
        break;
    }
}

Window::Window(const int w, const int h, const std::string_view &window_name) noexcept : width(w), height(h), windowName(window_name) {
    initWindow();
}
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::initWindow() {
    initializeGLFW();
    setHints();
    createWindow();
    centerWindow();
}

void Window::createWindow() {
    // Use std::unique_ptr with custom deleter
    window = glfwCreateWindow(width, height, windowName.data(), nullptr, nullptr);

    if(!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }
    glfwSetKeyCallback(window, keyCallback);
}

void Window::setHints() const {
    // Set GLFW context version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    // glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
}

void Window::initializeGLFW() {
    if(!glfwInit()) {
        spdlog::info("Failed to initialize GLFW");
        throw std::runtime_error("Failed to initialize GLFW.");
    }
    glfwSetErrorCallback(errorCallback);
}

std::string Window::formatMode(const GLFWvidmode *mode) const {
    return fmt::format("({}x{}, Bits rgb{}{}{}, RR:{}Hz)", mode->width, mode->height, mode->redBits, mode->greenBits, mode->blueBits,
                       mode->refreshRate);
}

void Window::centerWindow() {
    // vnd::Timer monitort("get primary Monitor");
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    if(!primaryMonitor) { throw std::runtime_error("Failed to get the primary monitor."); }
    // LINFO("{}", monitort);

    // vnd::Timer modet("get mode");
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    if(!mode) { throw std::runtime_error("Failed to get the video mode of the primary monitor."); }
    // LINFO("{}", modet);

    // vnd::Timer crepositiont("calculating for reposition");
    const int monitorWidth = mode->width;
    const int monitorHeight = mode->height;
    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    auto centerX = CALC_CENTRO(monitorWidth, windowWidth);
    auto centerY = CALC_CENTRO(monitorHeight, windowHeight);
    // LINFO("{}", crepositiont);

    // vnd::Timer wrepositiont("window reposition");
    glfwSetWindowPos(window, centerX, centerY);
    int posX = 0;
    int posY = 0;
    glfwGetWindowPos(window, &posX, &posY);
    if(posX != centerX || posY != centerY) { throw std::runtime_error("Failed to position the window at the center."); }
    // LINFO("{}", wrepositiont);
    int xPos;
    int yPos;
    float xScale;
    float yScale;
    int monitorPhysicalWidth;
    int monitorPhysicalHeight;
    // vnd::Timer tmonitorinfo("get monitor info");
    glfwGetMonitorPos(primaryMonitor, &xPos, &yPos);
    glfwGetMonitorContentScale(primaryMonitor, &xScale, &yScale);
    glfwGetMonitorPhysicalSize(primaryMonitor, &monitorPhysicalWidth, &monitorPhysicalHeight);
    // LINFO("{}", tmonitorinfo);

    glfwSetWindowUserPointer(window, this);
    glfwShowWindow(window);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { throw std::runtime_error("Failed to initialize GLAD"); }
    glfwSwapInterval(1);
    // LINFO("Monitor:\"{}\", Phys:{}x{}mm, Scale:({}/{}), Pos:({}/{})", glfwGetMonitorName(primaryMonitor), monitorPhysicalWidth,
    //       monitorPhysicalHeight, xScale, yScale, xPos, yPos);
    // LINFO("Monitor Mode:{}", formatMode(mode));
    // LINFO("Created the window {0}: (w: {1}, h: {2}, pos:({3}/{4}))", windowName.data(), width, height, centerX, centerY);
}
