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

#include <lw_instance.hh>
#include <vulkan/vulkan.hpp>

namespace lw {
  class PhysicalDevice {
    vk::PhysicalDevice m_physicalDevice;
    uint32_t m_graphicsIndex;
  public:
    PhysicalDevice(const Instance &instance);
    const vk::PhysicalDevice &get(void) const { return m_physicalDevice; }
    const uint32_t &getGraphicsIndex(void) const { return m_graphicsIndex; }
    void setGraphicsIndex(uint32_t i) { m_graphicsIndex = i; };
  };
}
