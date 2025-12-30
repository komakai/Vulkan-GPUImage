//
// Created by glumes on 2021/3/6.
//

#pragma once

#include <VulkanFilter.h>

class OffScreenFilter : public VulkanFilter{

public:

    OffScreenFilter(): VulkanFilter(kVertexShader, kFragmentShader) {}

    //virtual int init(VkDevice device, VkRenderPass renderPass, std::shared_ptr<AssetLoader> assetLoader) override ;


    int updateDescriptorSet(VkSampler ,VkImageView,VkImageLayout) override;

    int updateDescriptorSet(std::vector<VkDescriptorBufferInfo>& bufferInfo,std::vector<VkDescriptorImageInfo>& imageInfo) override;

protected:
    int createDescriptorLayout() override;
    int createDescriptorSet() override;

};
