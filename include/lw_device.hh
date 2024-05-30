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
    const vk::Device &getDevice(void) const { return m_device; }
  };
}
