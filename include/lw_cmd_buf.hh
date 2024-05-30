#pragma once

#include <lw_device.hh>
#include <vulkan/vulkan.hpp>

namespace lw {
  class CmdPool;

  enum class CmdBufType {
    Primary,
    Secondary
  };

  class CmdBuf {
    const Device &c_device;
    const CmdPool &c_cmdPool;
    const CmdBufType c_type;
    vk::CommandBuffer m_cmdBuf;
  public:
    CmdBuf(const Device &device, const CmdPool &cmd_pool, CmdBufType type);
    const CmdBufType &getType(void) const { return c_type; }
    const vk::CommandBuffer &getCmdBuf(void) const { return m_cmdBuf; }
  };
}
