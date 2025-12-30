//
// Created by glumes on 2021/3/7.
//

#include "ExposureFilter.h"

void ExposureFilter::setProgress(uint32_t progress) {
    exposure = FilterUtil::getProgress(static_cast<int>(progress), -10.0f, 10.0f);
    pushConstant[0] = exposure;
}

