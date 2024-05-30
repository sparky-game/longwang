#pragma once

#include <lw_device.hh>
#include <lw_cmd_buf.hh>
#include <vulkan/vulkan.hpp>

namespace lw {
  class CmdPool {
    const Device &c_device;
    vk::CommandPool m_cmdPool;
  public:
    CmdPool(const Device &device);
    ~CmdPool(void);
    const vk::CommandPool &getCmdPool(void) const { return m_cmdPool; }
    CmdBuf alloc(CmdBufType type) { return CmdBuf(c_device, *this, type); }
  };
}
