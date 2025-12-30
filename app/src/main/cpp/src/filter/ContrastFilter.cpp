//
// Created by glumes on 2021/3/8.
//

#include "ContrastFilter.h"

void ContrastFilter::setProgress(uint32_t progress) {
    contrast = FilterUtil::getProgress(static_cast<int>(progress), 0.0, 2.0f);
    pushConstant[0] = contrast;
}
