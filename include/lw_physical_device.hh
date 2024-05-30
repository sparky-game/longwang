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
