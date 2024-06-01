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
