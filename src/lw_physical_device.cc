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
#include <lw_physical_device.hh>

namespace lw {
  PhysicalDevice::PhysicalDevice(const Instance &instance) {
    std::vector<vk::PhysicalDevice> physical_devices { instance.get().enumeratePhysicalDevices() };
    if (physical_devices.empty()) throw std::runtime_error{"lw::PhysicalDevice -> no available devices"};
    for (const auto &pd : physical_devices) {
      vk::PhysicalDeviceProperties props { pd.getProperties() };
      if (props.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
        m_physicalDevice = pd;
        break;
      }
    }
    if (!m_physicalDevice) m_physicalDevice = physical_devices.front();
    std::cout << "lw::PhysicalDevice :: `" << m_physicalDevice.getProperties().deviceName << "`" << std::endl;
  }
}
