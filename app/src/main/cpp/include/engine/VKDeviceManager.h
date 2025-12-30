//
// Created by glumes on 2021/2/23.
//

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <Log.h>

class VKDeviceManager {

public:

    VKDeviceManager() = default;

    ~VKDeviceManager() = default;

    int createDevice(ANativeWindow* platformWindow, VkApplicationInfo* appInfo, bool enableValidationLayers = false);

    VkInstance instance{};
    VkPhysicalDevice physicalDevice{};
    VkPhysicalDeviceMemoryProperties memoryProperties{};
    VkDevice device{};

    uint32_t queueFamilyIndex{};


    VkSurfaceKHR surface{};
    VkQueue queue{};

    bool initialized = false;
};
