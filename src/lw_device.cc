#include <ranges>
#include <iostream>
#include <lw_device.hh>
#include <lw_physical_device.hh>

static auto enumerate(const auto &es) {
  return es | std::views::transform([i = 0](const auto &x) mutable {
    return std::make_pair(i++, x);
  });
}

namespace lw {
  Device::Device(const Instance &instance) : m_physicalDevice(instance) {
    std::vector<vk::QueueFamilyProperties> queue_family_props = m_physicalDevice.get().getQueueFamilyProperties();
    float queue_priority = 0;
    for (const auto &[i, qfp] : enumerate(queue_family_props)) {
      if (qfp.queueFlags & vk::QueueFlagBits::eGraphics) {
        m_physicalDevice.setGraphicsIndex(i);
        break;
      }
    }
    vk::DeviceQueueCreateInfo device_queue_ci(vk::DeviceQueueCreateFlags(),
                                              m_physicalDevice.getGraphicsIndex(),
                                              1,
                                              &queue_priority);
    vk::DeviceCreateInfo device_ci(vk::DeviceCreateFlags(), device_queue_ci);
    try {
      m_device = m_physicalDevice.get().createDevice(device_ci);
    }
    catch (vk::SystemError &err) {
      std::cerr << "lw::Device -> " << err.what() << std::endl;
      exit(1);
    }
    std::cout << "lw::Device :: created successfully" << std::endl;
  }

  Device::~Device(void) {
    m_device.destroy();
    std::cout << "lw::~Device :: destroyed successfully" << std::endl;
  }
}
