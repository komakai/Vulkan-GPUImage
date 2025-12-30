//
// Created by glumes on 2021/3/3.
//

#pragma once

#include <vulkan/vulkan.h>

typedef struct  FilterPipeline{
    VkDescriptorSetLayout descLayout_;
    VkDescriptorPool descPool_;
    VkDescriptorSet descSet_;
    VkPipelineLayout layout_;
    VkPipeline pipeline_;
    VkPipelineCache cache_;
} FilterPipeline;

typedef struct FilterContext{
    VkRenderPass renderPass;
    VkDevice  device;
    VkFramebuffer framebuffer;
} FilterContext;


typedef struct FilterBuffer{
    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;
    int indexCount;
} FilterBuffer;

typedef struct FilterFramebuffer{
    VkFramebuffer framebuffer;
    int width;
    int height;
} FilterFramebuffer;
