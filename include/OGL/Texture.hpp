/*
 * Created by gbian on 04/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "Shader.hpp"
#include "headers.hpp"

class Texture {
public:
    GLuint ID;
    GLenum type;
    Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    // Assigns a texture unit to a texture
    void texUnit(Shader &shader, const char *uniform, GLuint unit);
    // Binds a texture
    void Bind();
    // Unbinds a texture
    void Unbind();
    // Deletes a texture
    void Delete();
};
