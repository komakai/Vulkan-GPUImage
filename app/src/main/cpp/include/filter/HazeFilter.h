//
// Created by glumes on 2021/3/8.
//

#pragma once

#include <VulkanFilter.h>

static const std::string hazeShader = "haze.frag";

class HazeFilter : public VulkanFilter {

public:
    HazeFilter() : VulkanFilter(showVertexShader, hazeShader) {
        pushConstant.resize(2);
        pushConstant[0] = distance;
        pushConstant[1] = slope;
    }

    void setProgress(uint32_t progress) override;

protected:
    float distance = 0.2f;
    float slope = 0.0f;
};
