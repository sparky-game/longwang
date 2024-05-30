#include <iostream>
#include <lw_cmd_pool.hh>

namespace lw {
  CmdPool::CmdPool(const Device &device) : c_device{device} {
    vk::CommandPoolCreateInfo command_pool_ci { vk::CommandPoolCreateFlags(), c_device.getPhysicalDevice().getGraphicsIndex() };
    try {
      m_cmdPool = c_device.get().createCommandPool(command_pool_ci);
    }
    catch (vk::SystemError &err) {
      std::cerr << "lw::CmdPool -> " << err.what() << std::endl;
      throw err;
    }
    std::cout << "lw::CmdPool :: created successfully" << std::endl;
  }

  CmdPool::~CmdPool(void) {
    c_device.get().destroyCommandPool(m_cmdPool);
    std::cout << "lw::~CmdPool :: destroyed successfully" << std::endl;
  }
}
