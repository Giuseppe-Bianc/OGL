/*
 * Created by gbian on 04/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#include "../../include/OGL/VBO.hpp"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat *vertices, GLsizeiptr size) {
    vnd::AutoTimer t("VBO Creation");
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }

// Unbinds the VBO
void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// Deletes the VBO
void VBO::Delete() { glDeleteBuffers(1, &ID); }