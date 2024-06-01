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

#include <vulkan/vulkan.hpp>
#include <lw_physical_device.hh>

namespace lw {
  class Device {
    PhysicalDevice m_physicalDevice;
    vk::Device m_device;
  public:
    Device(const Instance &instance);
    ~Device(void);
    const PhysicalDevice &getPhysicalDevice(void) const { return m_physicalDevice; }
    const vk::Device &get(void) const { return m_device; }
  };
}
