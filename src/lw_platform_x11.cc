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

#include <iostream>
#include <xcb/xcb.h>
#include <X11/Xlib.h>
#include <lw_platform.hh>
#include <X11/Xlib-xcb.h>

static constexpr auto window_x {0};
static constexpr auto window_y {0};
static constexpr auto window_width { 1280 };
static constexpr auto window_height { 720 };
static constexpr std::string window_name { "Test" };
static constexpr std::string wm_protocols_prop_id { "WM_PROTOCOLS" };
static const std::string wm_delete_protocol_id { "WM_DELETE_WINDOW" };

xcb_connection_t *connection = 0;
xcb_window_t window = {0};

static inline void window_set_title(void) {
  xcb_change_property(connection,
                      XCB_PROP_MODE_REPLACE,
                      window,
                      XCB_ATOM_WM_NAME,
                      XCB_ATOM_STRING,
                      8,
                      window_name.size(),
                      window_name.c_str());
}

namespace lw {
  void platform_create_window(void) {
    Display *display = XOpenDisplay(0);
    connection = XGetXCBConnection(display);
    if (xcb_connection_has_error(connection)) {
      throw std::runtime_error{"lw::platform_create_window() -> unable to connect to X server via XCB"};
    }
    const struct xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_iterator_t i = xcb_setup_roots_iterator(setup);
    for (int32_t s = 0; s > 0; --s) xcb_screen_next(&i);
    xcb_screen_t *screen = i.data;
    window = xcb_generate_id(connection);
    uint32_t values[] = {
      screen->black_pixel,
      XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE |
      XCB_EVENT_MASK_KEY_PRESS      |
      XCB_EVENT_MASK_KEY_RELEASE    |
      XCB_EVENT_MASK_EXPOSURE       |
      XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_STRUCTURE_NOTIFY
    };
    xcb_create_window(connection,
                      XCB_COPY_FROM_PARENT,
                      window,
                      screen->root,
                      window_x,
                      window_y,
                      window_width,
                      window_height,
                      0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
                      values);
    window_set_title();
    xcb_intern_atom_cookie_t wm_delete_cookie = xcb_intern_atom(connection,
                                                                0,
                                                                wm_delete_protocol_id.size(),
                                                                wm_delete_protocol_id.c_str());
    xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(connection,
                                                                   0,
                                                                   wm_protocols_prop_id.size(),
                                                                   wm_protocols_prop_id.c_str());
    xcb_intern_atom_reply_t *wm_delete_reply = xcb_intern_atom_reply(connection, wm_delete_cookie, 0);
    xcb_intern_atom_reply_t *wm_protocols_reply = xcb_intern_atom_reply(connection, wm_protocols_cookie, 0);
    xcb_change_property(connection,
                        XCB_PROP_MODE_REPLACE,
                        window,
                        wm_protocols_reply->atom,
                        4,
                        32,
                        1,
                        &wm_delete_reply->atom);
    xcb_map_window(connection, window);
    if (xcb_flush(connection) <= 0) {
      throw std::runtime_error{"lw::platform_create_window() -> error when flushing the XCB stream"};
    }
    std::cout << "lw::platform_create_window() :: created successfully" << std::endl;
  }

  void platform_destroy_window(void) {
    xcb_destroy_window(connection, window);
    std::cout << "lw::platform_destroy_window() :: destroyed successfully" << std::endl;
  }

  void platform_get_required_extensions(std::vector<const char *> &extensions) {
    extensions.push_back("VK_KHR_xcb_surface");
  }
}

#endif  // __unix__
