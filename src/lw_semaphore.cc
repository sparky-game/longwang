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
#include <lw_semaphore.hh>

namespace lw {
  Semaphore::Semaphore(const Device &device) : c_device{device} {
    m_semaphore = c_device.get().createSemaphore({});
    std::cout << "lw::Semaphore :: created successfully" << std::endl;
  }

  Semaphore::~Semaphore(void) {
    c_device.get().destroySemaphore(m_semaphore);
    std::cout << "lw::~Semaphore :: destroyed successfully" << std::endl;
  }
}
