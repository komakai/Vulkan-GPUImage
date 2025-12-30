//
// Created by glumes on 2021/3/8.
//

#pragma once

#include <VulkanFilter.h>

static const std::string contrastShader = "contrast.frag";

class ContrastFilter : public VulkanFilter {

public:
    ContrastFilter() : VulkanFilter(showVertexShader, contrastShader) {
        pushConstant.resize(1);
        pushConstant[0] = contrast;
    }

    void setProgress(uint32_t progress) override;

protected:

private:
    float  contrast = 1.2f;
};
