//
// Created by glumes on 2021/3/7.
//

#include "GammaFilter.h"

void GammaFilter::setProgress(uint32_t progress) {
    gamma = FilterUtil::getProgress(static_cast<int>(progress), 0.0f, 3.0f);
    pushConstant[0] = gamma;
}
