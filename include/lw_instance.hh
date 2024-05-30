#pragma once

#include <vulkan/vulkan.hpp>

namespace lw {
  class Instance {
    vk::Instance m_instance;
  public:
    Instance(void);
    ~Instance(void);
    const vk::Instance &get(void) const { return m_instance; }
  };
}
