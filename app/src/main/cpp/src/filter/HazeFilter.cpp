//
// Created by glumes on 2021/3/8.
//

#include "HazeFilter.h"

void HazeFilter::setProgress(uint32_t progress) {
    distance = FilterUtil::getProgress(static_cast<int>(progress), -0.3f, 0.3f);
    slope = FilterUtil::getProgress(static_cast<int>(progress), -0.3f, 0.3f);
    pushConstant[0] = distance;
    pushConstant[1] = slope;
}
