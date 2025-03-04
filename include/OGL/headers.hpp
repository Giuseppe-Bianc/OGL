/*
 * Created by gbian on 03/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// NOLINTBEGIN(*-include-cleaner)
#pragma once

#include "ogl_lib_core/ogl_lib_core.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <glad/glad/glad.h>

[[nodiscard]] static constexpr auto calcolaCentro(const int &width, const int &w) noexcept { return (width - w) / 2; }
#define CALC_CENTRO(width, w) calcolaCentro(width, w)

// NOLINTEND(*-include-cleaner)