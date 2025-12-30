//
// Created by glumes on 2021/3/7.
//

#pragma once

#include <VulkanFilter.h>

class MirrorFilter :public VulkanFilter{

public:

    MirrorFilter():VulkanFilter(showVertexShader, reverseFragShader) {}

};
