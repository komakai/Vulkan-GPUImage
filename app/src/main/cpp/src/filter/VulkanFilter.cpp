//
// Created by glumes on 2021/2/28.
//

#include "VulkanFilter.h"
#include "ShaderUtils.h"
#include <cassert>


int VulkanFilter::createDescriptorLayout() {

/*    VkDescriptorSetLayoutBinding binding = vks::descriptorSetLayoutBinding(
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0);

    VkDescriptorSetLayoutCreateInfo info = vks::descriptorSetLayoutCreateInfo(&binding, 1);

    CALL_VK(vkCreateDescriptorSetLayout(context.device,&info, nullptr,&pipeline.descLayout_))

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = vks::pipelineLayoutCreateInfo(&pipeline.descLayout_,1);

    if (!pushConstant.empty()){
        VkPushConstantRange push_constant_ranges[1] = {};
        push_constant_ranges->stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        push_constant_ranges->offset = 0;
        push_constant_ranges->size = pushConstant.size() * sizeof(float);

        pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
        pipelineLayoutCreateInfo.pPushConstantRanges = push_constant_ranges;
    }

    CALL_VK(vkCreatePipelineLayout(context.device,&pipelineLayoutCreateInfo, nullptr,&pipeline.layout_))

    return VK_SUCCESS; */
    VkDescriptorSetLayoutBinding binding {
            0,
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            1,
            VK_SHADER_STAGE_FRAGMENT_BIT,
    };

    VkDescriptorSetLayoutCreateInfo info {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .bindingCount = 1,
            .pBindings = &binding,
    };

    CALL_VK(vkCreateDescriptorSetLayout(context.device,&info, nullptr,&pipeline.descLayout_))

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .setLayoutCount = 1,
            .pSetLayouts = &pipeline.descLayout_,
    };

    if (!pushConstant.empty()) {
        std::vector<VkPushConstantRange> push_constant_ranges;
        push_constant_ranges.push_back({
                                               VK_SHADER_STAGE_FRAGMENT_BIT,
                                               0,
                                               static_cast<uint32_t>(pushConstant.size() * sizeof(decltype(pushConstant)::value_type)),
                                       });

        pipelineLayoutCreateInfo.pushConstantRangeCount = static_cast<uint32_t>(push_constant_ranges.size());
        pipelineLayoutCreateInfo.pPushConstantRanges = push_constant_ranges.data();
    }

    CALL_VK(vkCreatePipelineLayout(context.device,&pipelineLayoutCreateInfo, nullptr,&pipeline.layout_))

    return VK_SUCCESS;
}

int VulkanFilter::createDescriptorSet() {
/*    VkDescriptorPoolSize size = vks::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                        1);
    VkDescriptorPoolCreateInfo poolCreateInfo = vks::descriptorPoolCreateInfo(1, &size, 1);

    CALL_VK(vkCreateDescriptorPool(context.device,&poolCreateInfo, nullptr,&pipeline.descPool_))

    VkDescriptorSetAllocateInfo allocateInfo = vks::descriptorSetAllocateInfo(pipeline.descPool_,&pipeline.descLayout_,1);

    CALL_VK(vkAllocateDescriptorSets(context.device,&allocateInfo,&pipeline.descSet_))
    return VK_SUCCESS;*/
    VkDescriptorPoolSize poolSize {
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            1
    };

    VkDescriptorPoolCreateInfo poolCreateInfo{
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .maxSets = 1,
            .poolSizeCount = 1,
            .pPoolSizes = &poolSize,
    };

    CALL_VK(vkCreateDescriptorPool(context.device,&poolCreateInfo, nullptr,&pipeline.descPool_))

    VkDescriptorSetAllocateInfo allocateInfo = vks::descriptorSetAllocateInfo(pipeline.descPool_,&pipeline.descLayout_,1);

    CALL_VK(vkAllocateDescriptorSets(context.device,&allocateInfo,&pipeline.descSet_))
    return VK_SUCCESS;
}

int VulkanFilter::updateDescriptorSet(VkSampler sampler,VkImageView imageView,VkImageLayout imageLayout) {
    VkDescriptorImageInfo texDsts[1];
    memset(texDsts, 0, sizeof(texDsts));
    texDsts->sampler = sampler;
    texDsts->imageView = imageView;
    texDsts->imageLayout = imageLayout;
    VkWriteDescriptorSet writeDst = vks::writeDescriptorSet(pipeline.descSet_,
                                                            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                                            0,
                                                            texDsts);

    vkUpdateDescriptorSets(context.device, 1, &writeDst, 0, nullptr);
    return VK_SUCCESS;
}

int VulkanFilter::buildRenderPass(VkCommandBuffer commandBuffer,VkRenderPass renderPass,VkFramebuffer framebuffer) {

    VkClearValue clearVals{ .color { .float32 {0.0f, 0.0f, 0.0f, 1.0f}}};

    VkRenderPassBeginInfo offRenderInfo{
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = renderPass,
            .framebuffer = framebuffer,
            .renderArea {
                    .extent {
                            .width = static_cast<uint32_t>(width),
                            .height = static_cast<uint32_t>(height)
                    }
            },
            .clearValueCount = 1,
            .pClearValues = &clearVals,
    };

    vkCmdBeginRenderPass(commandBuffer, &offRenderInfo, VK_SUBPASS_CONTENTS_INLINE);

    if (!pushConstant.empty()){
        vkCmdPushConstants(commandBuffer,pipeline.layout_,VK_SHADER_STAGE_FRAGMENT_BIT,0, static_cast<uint32_t>(pushConstant.size() * sizeof(decltype(pushConstant)::value_type)), pushConstant.data());
    }

    VkViewport viewport = vks::viewport((float)width,(float)height,0.0f,1.0f);
    vkCmdSetViewport(commandBuffer,0,1,&viewport);

    VkRect2D scissor = vks::rect2D(width,height,0,0);
    vkCmdSetScissor(commandBuffer,0,1,&scissor);

    vkCmdBindPipeline(commandBuffer,
                      VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline_);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipeline.layout_, 0, 1,
                            &pipeline.descSet_, 0, nullptr);

    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, &offset);

    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);

    vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);

//    vkCmdDraw(commandBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    return VK_SUCCESS;
}



int VulkanFilter::createPipelineCache() {
    VkPipelineCacheCreateInfo cacheCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .initialDataSize = 0,
            .pInitialData = nullptr,
    };

    CALL_VK(vkCreatePipelineCache(context.device, &cacheCreateInfo, nullptr, &pipeline.cache_))
    return 0;
}


int VulkanFilter::createPipeline(VkRenderPass renderPass) {

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .flags = 0,
            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            .primitiveRestartEnable = VK_FALSE,
    };

    VkVertexInputBindingDescription inputBindingDescription {
        0,
        5 * sizeof(float) ,
        VK_VERTEX_INPUT_RATE_VERTEX
    };

    VkVertexInputAttributeDescription inputAttributeDescription [2] = {
            {
                    0,
                    0,
                    VK_FORMAT_R32G32B32_SFLOAT,
                    0
            },
            {
                    1,
                    0,
                    VK_FORMAT_R32G32_SFLOAT,
                    sizeof(float) * 3
            }
    };
    VkPipelineVertexInputStateCreateInfo inputStateCreateInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            .vertexBindingDescriptionCount = 1,
            .pVertexBindingDescriptions = &inputBindingDescription,
            .vertexAttributeDescriptionCount = 2,
            .pVertexAttributeDescriptions = inputAttributeDescription,
    };

    // 绘制的方向不对也会导致渲染黑屏的
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo{
            .sType =VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            .polygonMode = VK_POLYGON_MODE_FILL,
            .cullMode = VK_CULL_MODE_NONE,
            .frontFace = VK_FRONT_FACE_CLOCKWISE,
            .lineWidth = 1.0f
    };

    VkPipelineColorBlendAttachmentState blendAttachmentState {
        .blendEnable = VK_FALSE,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
    };
    VkPipelineColorBlendStateCreateInfo blendStateCreateInfo {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &blendAttachmentState
    };

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .viewportCount = 1,
            .scissorCount = 1
    };

    VkPipelineMultisampleStateCreateInfo multisampleState{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
    };

    std::vector<VkDynamicState> dynamicStateEnables = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR
    };
    VkPipelineDynamicStateCreateInfo dynamicState {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = static_cast<uint32_t>(dynamicStateEnables.size()),
        .pDynamicStates = dynamicStateEnables.data()
    };

    VkShaderModule vertexShader = loadShader(vertShader, m_assetLoader, VK_SHADER_STAGE_VERTEX_BIT, context.device);
    VkShaderModule fragmentShader = loadShader(fragShader, m_assetLoader, VK_SHADER_STAGE_FRAGMENT_BIT, context.device);

    VkPipelineShaderStageCreateInfo shaderStages[2]{
            {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .stage = VK_SHADER_STAGE_VERTEX_BIT,
                    .module = vertexShader,
                    .pName = "main",
                    .pSpecializationInfo = nullptr,
            },
            {
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    .pNext = nullptr,
                    .flags = 0,
                    .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
                    .module = fragmentShader,
                    .pName = "main",
                    .pSpecializationInfo = nullptr,
            }};

    VkGraphicsPipelineCreateInfo pipelineCreateInfo {
            .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            .stageCount = 2,
            .pStages = shaderStages,
            .pVertexInputState = &inputStateCreateInfo,
            .pInputAssemblyState = &inputAssemblyStateCreateInfo,
            .pViewportState = &viewportStateCreateInfo,
            .pRasterizationState = &rasterizationStateCreateInfo,
            .pMultisampleState = &multisampleState,
            .pColorBlendState = &blendStateCreateInfo,
            .pDynamicState = &dynamicState,
            .layout = pipeline.layout_,
            .renderPass = renderPass,
    };

    CALL_VK(vkCreateGraphicsPipelines(context.device, pipeline.cache_, 1, &pipelineCreateInfo,
                                      nullptr, &pipeline.pipeline_))

    vkDestroyShaderModule(context.device,vertexShader, nullptr);
    vkDestroyShaderModule(context.device,fragmentShader, nullptr);
    return VK_SUCCESS;
}

int VulkanFilter::init(VkDevice device, VkRenderPass renderPass, const std::shared_ptr<AssetLoader>& assetLoader) {
    if (isInit){
        return VK_SUCCESS;
    }
    context.device = device;
    context.renderPass = renderPass;
    m_assetLoader = assetLoader;
    createDescriptorLayout();
    createPipelineCache();
    createPipeline();
    createDescriptorSet();
    isInit = true;
    return 0;
}

int VulkanFilter::createPipeline() {
    createPipeline(context.renderPass);
    return 0;
}

int VulkanFilter::bindFilterBuffer(FilterBuffer &buffer) {
    indexBuffer = buffer.indexBuffer;
    vertexBuffer = buffer.vertexBuffer;
    indexCount = buffer.indexCount;
    return 0;
}

int VulkanFilter::bindFilterFramebuffer(FilterFramebuffer &framebuffer) {
    context.framebuffer = framebuffer.framebuffer;
    width = framebuffer.width;
    height = framebuffer.height;
    return 0;
}

int VulkanFilter::buildRenderPass(VkCommandBuffer commandBuffer) {
    buildRenderPass(commandBuffer,context.renderPass,context.framebuffer);
    return 0;
}

int VulkanFilter::updateDescriptorSet(std::vector<VkDescriptorBufferInfo>& bufferInfo,std::vector<VkDescriptorImageInfo>& imageInfo) {

    std::vector<VkWriteDescriptorSet> writeDst ;

    writeDst.push_back(vks::writeDescriptorSet(pipeline.descSet_,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1,bufferInfo.data(),bufferInfo.size()));

    writeDst.push_back(vks::writeDescriptorSet(pipeline.descSet_,VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,0,imageInfo.data(),imageInfo.size()));

    vkUpdateDescriptorSets(context.device,writeDst.size(),writeDst.data(),0, nullptr);

    return VK_SUCCESS;
}

int VulkanFilter::updateBufferDescriptorSet(std::vector<VkDescriptorBufferInfo> &bufferInfo,int binding) {
    std::vector<VkWriteDescriptorSet> writeDst ;
    writeDst.push_back(vks::writeDescriptorSet(pipeline.descSet_,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,binding,bufferInfo.data(),bufferInfo.size()));
    vkUpdateDescriptorSets(context.device,writeDst.size(),writeDst.data(),0, nullptr);
    return VK_SUCCESS;
}

int VulkanFilter::updateImageDescriptorSet(std::vector<VkDescriptorImageInfo> &imageInfo,int binding ) {
    std::vector<VkWriteDescriptorSet> writeDst ;
    writeDst.push_back(vks::writeDescriptorSet(pipeline.descSet_,VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,binding,imageInfo.data(),imageInfo.size()));
    vkUpdateDescriptorSets(context.device,writeDst.size(),writeDst.data(),0, nullptr);
    return VK_SUCCESS;
}

void VulkanFilter::setProgress(uint32_t progress) {
    mProgress = progress;
}
