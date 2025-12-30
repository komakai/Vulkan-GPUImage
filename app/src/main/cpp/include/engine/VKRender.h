//
// Created by glumes on 2021/2/23.
//

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <Log.h>

class VKDeviceManager;

class VKSwapChainManager;

class VKBufferManager;


class VKOffScreen;

class VulkanFilter;

class OffScreenFilter;

class EffectFilter;

class VKRender {

public:
    VKRender() = default;

    ~VKRender() = default;


    int createRenderPass(VKDeviceManager *deviceInfo, VKSwapChainManager *swapChainInfo);

    int createCommandPool(VKDeviceManager *deviceInfo, VKSwapChainManager *swapChainInfo,
                          VKBufferManager *bufferInfo,
                          VKOffScreen *vkOffScreenInfo,
                          VulkanFilter * filter, OffScreenFilter* offScreenFilter, VulkanFilter* effectFilter);

    int deleteCommandPool(VKDeviceManager *deviceInfo) const;

    void setImageLayout(VkCommandBuffer cmdBuffer,
                        VkImage image,
                        VkImageLayout oldImageLayout,
                        VkImageLayout newImageLayout,
                        VkPipelineStageFlags srcStages,
                        VkPipelineStageFlags destStages);


    VkRenderPass renderPass;
    VkCommandPool cmdPool;
    std::unique_ptr<VkCommandBuffer[]> cmdBuffer;
    uint32_t cmdBufferLen;
    VkSemaphore semaphore;
    VkFence fence;

};
