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


#pragma once

#include <vulkan/vulkan.hpp>

namespace lw {
  class Instance {
    const std::string &m_name;
    vk::Instance m_instance;
    std::vector<const char *> m_extensions;
  public:
    Instance(const std::string &name);
    ~Instance(void);
    const vk::Instance &get(void) const { return m_instance; }
    const std::string &getName(void) const { return m_name; }
  };
}
