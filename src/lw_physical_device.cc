#include <iostream>
#include <lw_physical_device.hh>

namespace lw {
  PhysicalDevice::PhysicalDevice(const Instance &instance) {
    std::vector<vk::PhysicalDevice> physical_devices = instance.get().enumeratePhysicalDevices();
    if (physical_devices.empty()) {
      std::cerr << "lw::PhysicalDevice -> no available devices" << std::endl;
      exit(1);
    }
    for (const auto &pd : physical_devices) {
      vk::PhysicalDeviceProperties props = pd.getProperties();
      if (props.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
        m_physicalDevice = pd;
        break;
      }
    }
    if (!m_physicalDevice) m_physicalDevice = physical_devices.front();
    std::cout << "lw::PhysicalDevice :: " << m_physicalDevice.getProperties().deviceName << std::endl;
  }
}
