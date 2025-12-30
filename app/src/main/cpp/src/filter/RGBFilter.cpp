//
// Created by glumes on 2021/3/7.
//

#include "RGBFilter.h"
#include "ShaderUtils.h"
#include <FilterUtil.h>
#include <cassert>

void RGBFilter::setProgress(uint32_t progress) {
    green = FilterUtil::getProgress(static_cast<int>(progress), 0.0, 1.0f);
    pushConstant[1] = green;
}
