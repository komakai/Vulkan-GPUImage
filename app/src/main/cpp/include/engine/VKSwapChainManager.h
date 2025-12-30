//
// Created by glumes on 2021/2/23.
//

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <Log.h>

class VKDeviceManager;
class VKRender;

class VKSwapChainManager {

public:
    VKSwapChainManager() = default;

    ~VKSwapChainManager() = default;

    int createSwapChain(VKDeviceManager* info);

    int createFrameBuffer(VKDeviceManager *deviceInfo, VKRender * renderInfo, VkImageView depthView =  VK_NULL_HANDLE);



    VkSwapchainKHR swapchain;
    uint32_t swapchainLength;

    VkExtent2D displaySize;
    VkFormat displayFormat;

    // array of frame buffers and views
    std::unique_ptr<VkFramebuffer[]> framebuffers;
    std::unique_ptr<VkImage[]> displayImages;
    std::unique_ptr<VkImageView[]> displayViews;
};
