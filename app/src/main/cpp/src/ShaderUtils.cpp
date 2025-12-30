//
// Created by Giles Payne on 2025/12/20.
//

#include "ShaderUtils.h"
#include "Log.h"
#include <cassert>

std::string getShadersDir() {
    return "shaders/";
}

std::string getShadersExt() {
    return ".spv";
}

VkShaderModule loadShader(const std::string& shaderName, const std::shared_ptr<AssetLoader>& assetLoader,
                          VkShaderStageFlagBits type, VkDevice device) {
    std::vector<uint8_t> buffer;
    std::string shaderPath = getShadersDir() + shaderName + getShadersExt();
    assetLoader->loadAsset(shaderPath, buffer);

    VkShaderModuleCreateInfo createInfo = {
            VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            nullptr,
            0,
            buffer.size(),
            reinterpret_cast<const uint32_t *>(buffer.data())
    };

    VkShaderModule shaderModule;
    CALL_VK(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule));
    return shaderModule;
}