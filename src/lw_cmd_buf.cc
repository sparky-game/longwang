#include <iostream>
#include <lw_cmd_buf.hh>
#include <lw_cmd_pool.hh>

static constexpr auto buf_alloc_count {1};

namespace lw {
  CmdBuf::CmdBuf(const Device &device, const CmdPool &cmd_pool, CmdBufType type) : c_device{device}, c_cmdPool{cmd_pool}, c_type{type} {
    vk::CommandBufferAllocateInfo cmd_buf_ai{c_cmdPool.get(),
                                             c_type == CmdBufType::Primary ? vk::CommandBufferLevel::ePrimary : vk::CommandBufferLevel::eSecondary,
                                             buf_alloc_count};
    try {
      m_cmdBuf = c_device.get().allocateCommandBuffers(cmd_buf_ai).front();
    }
    catch (vk::SystemError &err) {
      std::cerr << "lw::CmdBuf -> " << err.what() << std::endl;
      throw err;
    }
    std::cout << "lw::CmdBuf :: allocated successfully" << std::endl;
  }
}
