/*
 * Created by gbian on 04/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "headers.hpp"

class VBO {
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID{};
    // Constructor that generates a Vertex Buffer Object and links it to vertices
    VBO(GLfloat *vertices, GLsizeiptr size);

    // Binds the VBO
    void Bind();
    // Unbinds the VBO
    void Unbind();
    // Deletes the VBO
    void Delete();
};