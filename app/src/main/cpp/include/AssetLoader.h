//
// Created by Giles Payne on 2025/12/20.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <android/asset_manager.h>

class AssetLoader {
public:
    explicit AssetLoader(AAssetManager* manager) : pAssetManager(manager) {}
    virtual ~AssetLoader() = default;

    static std::shared_ptr<AssetLoader> create(AAssetManager* pAssetManager);
    virtual void loadAsset(const std::string& filePath, std::vector<uint8_t>& buffer) const;

protected:;
    AAssetManager* pAssetManager;
};
