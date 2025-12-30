#pragma once

#include <vulkan/vulkan_core.h>
#include "AssetLoader.h"

VkShaderModule loadShader(const std::string& shaderName, const std::shared_ptr<AssetLoader> &assetLoader,
                          VkShaderStageFlagBits type, VkDevice device);
