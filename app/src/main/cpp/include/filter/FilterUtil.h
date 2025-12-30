//
// Created by glumes on 2021/3/7.
//

#pragma once

class VulkanFilter;

class FilterUtil {
public:
    static VulkanFilter* getFilterByType(int type);

    static float getProgress(int progress, float start, float end);
};
