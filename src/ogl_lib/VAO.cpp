/*
 * Created by gbian on 04/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#include "OGL/VAO.hpp"

// Constructor that generates a VAO ID
VAO::VAO() {
    vnd::AutoTimer t("VAO Generation");
    glGenVertexArrays(1, &ID);
}

DISABLE_WARNINGS_PUSH(4244)
// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) {
    vnd::AutoTimer t("VAO Linking");
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}
DISABLE_WARNINGS_POP()

// Binds the VAO
void VAO::Bind() { glBindVertexArray(ID); }

// Unbinds the VAO
void VAO::Unbind() { glBindVertexArray(0); }

// Deletes the VAO
void VAO::Delete() { glDeleteVertexArrays(1, &ID); }
