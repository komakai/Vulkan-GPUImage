//
// Created by glumes on 2021/3/7.
//

#pragma once

#include <VulkanFilter.h>

static const std::string gammaShader = "gamma.frag";

class GammaFilter : public VulkanFilter {

public:
    GammaFilter() : VulkanFilter(showVertexShader, gammaShader) {
        pushConstant.resize(1);
        pushConstant[0] = gamma;
    }

    void setProgress(uint32_t progress) override;

protected:
    float  gamma = 1.2f;
};
