//
// Created by glumes on 2021/3/7.
//

#pragma once

#include <VulkanFilter.h>

static const std::string exposureShader = "exposure.frag";

class ExposureFilter : public VulkanFilter {

public:
    ExposureFilter() : VulkanFilter(showVertexShader, exposureShader) {
        pushConstant.resize(1);
        pushConstant[0] = exposure;
    }

    void setProgress(uint32_t progress) override;

protected:
    float  exposure = 1.0f;
};
