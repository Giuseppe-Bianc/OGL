/*
 * Created by gbian on 04/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "headers.hpp"

std::string get_file_contents(const std::string &filename);
class Shader {
public:
    Shader() = default;
    GLuint ID{};
    Shader(const char *vertexPath, const char *fragmentPath);
    void Activate();
    void Delete();

private:
    // Checks if the different Shaders have compiled properly
    void compileErrors(unsigned int shader, const char *type);
};
