//
// Created by Giles Payne on 2025/12/20.
//

#include "AssetLoader.h"

std::shared_ptr<AssetLoader> AssetLoader::create(AAssetManager *pAssetManager) {
    return std::make_shared<AssetLoader>(pAssetManager);
}

void AssetLoader::loadAsset(const std::string &filePath, std::vector <uint8_t> &buffer) const {
    AAsset* file = AAssetManager_open(pAssetManager,filePath.data(), AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    buffer.resize(fileLength);
    AAsset_read(file, buffer.data(), fileLength);
    AAsset_close(file);
}
