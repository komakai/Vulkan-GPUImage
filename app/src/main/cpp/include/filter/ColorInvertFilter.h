//
// Created by glumes on 2021/3/7.
//

#pragma once

#include <VulkanFilter.h>

static const std::string colorInvertShader = "colorinvert.frag";

class ColorInvertFilter :public VulkanFilter{

public:
    ColorInvertFilter():VulkanFilter(showVertexShader, colorInvertShader) {}
};
