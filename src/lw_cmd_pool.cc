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
#include <lw_cmd_pool.hh>

namespace lw {
  CmdPool::CmdPool(const Device &device) : c_device{device} {
    vk::CommandPoolCreateInfo command_pool_ci { {}, c_device.getPhysicalDevice().getGraphicsIndex() };
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

  void CmdPool::reset(void) const {
    try {
      c_device.get().resetCommandPool(m_cmdPool);
    }
    catch (vk::SystemError &err) {
      std::cerr << "lw::CmdPool -> " << err.what() << std::endl;
      throw err;
    }
  }
}
