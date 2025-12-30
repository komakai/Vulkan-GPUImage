//
// Created by glumes on 2021/2/23.
//

#pragma once

#include "VideoRenderer.h"
#include <vulkan/vulkan.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <FilterUtil.h>

class VKDeviceManager;
class VKSwapChainManager;
class VKRender;
class VKBufferManager;
class VKTextureManager;
class VKOffScreen;
class VulkanFilter;
class OffScreenFilter;
class EffectFilter;
class MirrorFilter;

class VKEngineRenderer : public VideoRenderer{

public:
    VKEngineRenderer();
    ~VKEngineRenderer() override;

    void init(ANativeWindow* window, size_t width, size_t height,AAssetManager* manager) override;
    void render() override;
    void updateFrame(const video_frame& frame) override;
    void draw(uint8_t *buffer, size_t length, size_t width, size_t height, int rotation) override;
    void setParameters(uint32_t params) override;
    void setProgress(uint32_t progress) override;
    uint32_t getParameters() override;
    bool createTextures() override;
    bool updateTextures() override;
    void deleteTextures() override;

private:

    void createDevice(ANativeWindow* platformWindow, VkApplicationInfo* appInfo);
    void createSwapChain();
    void createRenderPass();
    void createFrameBuffers(VkImageView depthView = VK_NULL_HANDLE);

    void createUniformBuffers();
    void createVertexBuffer();
    void createIndexBuffer();

    void createCommandPool();

    void deleteUniformBuffers();
    void deleteCommandPool();


    VKDeviceManager* vkDeviceInfo;
    VKSwapChainManager* vkSwapChainInfo;
    VKRender* vkRenderInfo;
    VKBufferManager* vkBufferInfo;
    VKTextureManager* vkTextureInfo;
    VKOffScreen* vkOffScreenInfo;

    uint8_t *m_pBuffer;
    size_t m_length;

    VulkanFilter *vulkanFilter;
    OffScreenFilter *offscreenFilter;
    VulkanFilter* effectFilter;

    size_t m_filter = 0;
    uint32_t m_CurrentProgress = 0;
    uint32_t m_LastProgress = 0;

    void createOffscreenReaderPassAndFramebuffer();

    bool m_enableValidationLayers = false;

    static bool checkValidationLayerSupport();
};
