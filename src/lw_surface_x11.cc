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


#ifdef __unix__

#define VK_USE_PLATFORM_XCB_KHR

#include <iostream>
#include <xcb/xcb.h>
#include <lw_surface.hh>
#include <lw_platform.hh>

extern xcb_connection_t *connection;
extern xcb_window_t window;

namespace lw {
  Surface::Surface(const Instance &instance, const uint32_t &win_width, const uint32_t &win_height) : c_instance{instance}, c_win_width{win_width}, c_win_height{win_height} {
    platform_create_window(c_win_width, c_win_height, c_instance.getName());
    vk::XcbSurfaceCreateInfoKHR surface_ci { {}, connection, window };
    try {
      m_surface = c_instance.get().createXcbSurfaceKHR(surface_ci);
    }
    catch (vk::SystemError &err) {
      std::cerr << "lw::Surface -> " << err.what() << std::endl;
      throw err;
    }
    std::cout << "lw::Surface :: created successfully" << std::endl;
  }

  Surface::~Surface(void) {
    c_instance.get().destroySurfaceKHR(m_surface);
    std::cout << "lw::~Surface :: destroyed successfully" << std::endl;
    platform_destroy_window();
  }
}

#endif  // __unix__
