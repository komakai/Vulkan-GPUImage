//
// Created by glumes on 2021/3/7.
//

#pragma once

#include <VulkanFilter.h>

static const std::string rgbFragShader = "rgb.frag";

class RGBFilter : public VulkanFilter {

public:
    RGBFilter() : VulkanFilter(showVertexShader, rgbFragShader) {
        pushConstant.resize(3);
        pushConstant[0] = red;
        pushConstant[1] = green;
        pushConstant[2] = blue;
    };

    void setProgress(uint32_t progress) override;

protected:
    float red = 1.0;
    float green = 1.0;
    float blue = 1.0;
};
