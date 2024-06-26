/*
 * BSD Longwang --- A high performance Vulkan RaaL (Renderer as a Library)
 * Copyright (C) 2024 Wasym A. Alonso
 *
 * This file is part of Longwang.
 *
 * Longwang is free software: you can redistribute it and/or modify
 * it under the terms of the BSD 3-Clause "New" or "Revised" License
 * as published by The Regents of the University of California.
 *
 * Longwang is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * BSD 3-Clause "New" or "Revised" License for more details.
 *
 * You should have received a copy of the BSD 3-Clause "New" or
 * "Revised" License along with Longwang.
 * If not, see <https://opensource.org/license/BSD-3-Clause>.
 */


#pragma once

#include "lw_instance.hh"
#include <vulkan/vulkan.hpp>

namespace lw {
  class Surface {
    const Instance &c_instance;
    uint32_t m_winWidth;
    uint32_t m_winHeight;
    vk::SurfaceKHR m_surface;
  public:
    Surface(const Instance &instance, uint32_t win_width, uint32_t win_height);
    ~Surface(void);
    const vk::SurfaceKHR &get(void) const { return m_surface; }
    uint32_t getWidth(void) const { return m_winWidth; }
    uint32_t getHeight(void) const { return m_winHeight; }
  };
}
