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


#include <iostream>
#include <lw_instance.hh>
#include <lw_platform.hh>

static constexpr auto app_name { "Test" };
static constexpr auto app_version { VK_MAKE_VERSION(0, 1, 0) };
static constexpr auto engine_name { "Longwang" };
static constexpr auto engine_version { VK_MAKE_VERSION(0, 1, 0) };
static constexpr auto api_version { VK_API_VERSION_1_3 };
#ifndef NDEBUG
static constexpr const char *layers[] {{ "VK_LAYER_KHRONOS_validation" }};
static constexpr auto layer_count { sizeof(layers) / sizeof(layers[0]) };
#endif

namespace lw {
  Instance::Instance(void) {
    vk::ApplicationInfo app_i { app_name, app_version, engine_name, engine_version, api_version };
    m_extensions.push_back("VK_KHR_surface");
    platform_get_required_extensions(m_extensions);
    vk::InstanceCreateInfo instance_ci { {}, &app_i, {}, {}, static_cast<uint32_t>(m_extensions.size()), &m_extensions[0] };
#ifndef NDEBUG
    instance_ci.enabledLayerCount = layer_count;
    instance_ci.ppEnabledLayerNames = layers;
#endif
    try {
      m_instance = vk::createInstance(instance_ci);
    }
    catch (vk::SystemError &err) {
      std::cerr << "lw::Instance -> " << err.what() << std::endl;
      throw err;
    }
    std::cout << "lw::Instance :: created successfully" << std::endl;
  }

  Instance::~Instance(void) {
    m_instance.destroy();
    std::cout << "lw::~Instance :: destroyed successfully" << std::endl;
  }
}
