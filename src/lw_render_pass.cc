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
#include <lw_render_pass.hh>

namespace lw {
  RenderPass::RenderPass(const Device &device, const Surface &surface) : c_device{device}, c_surface{surface} {
    std::vector<vk::SurfaceFormatKHR> formats = c_device.getPhysicalDevice().get().getSurfaceFormatsKHR(c_surface.get());
    if (formats.empty()) throw std::runtime_error{"lw::RenderPass -> no available formats"};
    vk::Format color_fmt = formats.front().format == vk::Format::eUndefined ? vk::Format::eB8G8R8A8Unorm : formats.front().format;
    vk::AttachmentReference color_ref { 0, vk::ImageLayout::eColorAttachmentOptimal };
    vk::Format depth_fmt { vk::Format::eD16Unorm };
    vk::AttachmentReference depth_ref { 1, vk::ImageLayout::eDepthStencilAttachmentOptimal };
    std::array<vk::AttachmentDescription, 2> attachment_descriptions {
      vk::AttachmentDescription{{},
        color_fmt,
        vk::SampleCountFlagBits::e1,
        vk::AttachmentLoadOp::eClear,
        vk::AttachmentStoreOp::eStore,
        vk::AttachmentLoadOp::eDontCare,
        vk::AttachmentStoreOp::eDontCare,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::ePresentSrcKHR},
      vk::AttachmentDescription{{},
        depth_fmt,
        vk::SampleCountFlagBits::e1,
        vk::AttachmentLoadOp::eClear,
        vk::AttachmentStoreOp::eDontCare,
        vk::AttachmentLoadOp::eDontCare,
        vk::AttachmentStoreOp::eDontCare,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eDepthStencilAttachmentOptimal}
    };
    vk::SubpassDescription subpass_description{ {}, vk::PipelineBindPoint::eGraphics, {}, color_ref, {}, &depth_ref };
    vk::RenderPassCreateInfo render_pass_ci { {}, attachment_descriptions, subpass_description };
    try { m_renderPass = c_device.get().createRenderPass(render_pass_ci); }
    catch (vk::SystemError &err) {
      std::cerr << "lw::RenderPass -> " << err.what() << std::endl;
      throw err;
    }
    std::cout << "lw::RenderPass :: created successfully" << std::endl;
  }

  RenderPass::~RenderPass(void) {
    c_device.get().destroyRenderPass(m_renderPass);
    std::cout << "lw::~RenderPass :: destroyed successfully" << std::endl;
  }
}
