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


#include <limits>
#include <iostream>
#include <algorithm>
#include <lw_utils.hh>
#include <lw_swapchain.hh>

namespace lw {
  Swapchain::Swapchain(const Device &device, const Surface &surface) : c_device{device}, c_surface{surface} {
    vk::SurfaceCapabilitiesKHR surface_caps = c_device.getPhysicalDevice().get().getSurfaceCapabilitiesKHR(c_surface.get());
    std::vector<vk::SurfaceFormatKHR> formats = c_device.getPhysicalDevice().get().getSurfaceFormatsKHR(c_surface.get());
    if (formats.empty()) throw std::runtime_error{"lw::Swapchain -> no available formats"};
    vk::Format format = formats.front().format == vk::Format::eUndefined ? vk::Format::eB8G8R8A8Unorm : formats.front().format;
    vk::Extent2D swapchain_ex { 1280, 720 };
    if (surface_caps.currentExtent.width != std::numeric_limits<uint32_t>::max()) swapchain_ex = surface_caps.currentExtent;
    swapchain_ex.width = clamp(swapchain_ex.width, surface_caps.minImageExtent.width, surface_caps.maxImageExtent.width);
    swapchain_ex.height = clamp(swapchain_ex.height, surface_caps.minImageExtent.height, surface_caps.maxImageExtent.height);
    vk::SurfaceTransformFlagBitsKHR pre_transform = surface_caps.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity
      ? vk::SurfaceTransformFlagBitsKHR::eIdentity
      : surface_caps.currentTransform;
    vk::CompositeAlphaFlagBitsKHR comp_alpha = surface_caps.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied
      ? vk::CompositeAlphaFlagBitsKHR::ePreMultiplied
      : surface_caps.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
      ? vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
      : surface_caps.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::eInherit
      ? vk::CompositeAlphaFlagBitsKHR::eInherit
      : vk::CompositeAlphaFlagBitsKHR::eOpaque;
    vk::SwapchainCreateInfoKHR swapchain_ci({},
                                            c_surface.get(),
                                            surface_caps.minImageCount,
                                            format,
                                            vk::ColorSpaceKHR::eSrgbNonlinear,
                                            swapchain_ex,
                                            1,
                                            vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst,
                                            vk::SharingMode::eExclusive,
                                            {},
                                            pre_transform,
                                            comp_alpha,
                                            vk::PresentModeKHR::eFifo,
                                            true,
                                            nullptr);
    try { m_swapchain = c_device.get().createSwapchainKHR(swapchain_ci); }
    catch (vk::SystemError &err) {
      std::cerr << "lw::Swapchain -> " << err.what() << std::endl;
      throw err;
    }
    std::cout << "lw::Swapchain :: created successfully" << std::endl;
  }

  Swapchain::~Swapchain(void) {
    c_device.get().destroySwapchainKHR(m_swapchain);
    std::cout << "lw::~Swapchain :: destroyed successfully" << std::endl;
  }
}
