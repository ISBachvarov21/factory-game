#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <filesystem>
#include <unordered_map>

#include "Ids.h"

class AssetManager {
    using filepath=std::filesystem::path;
    std::unordered_map<AssetId, filepath> assets;

public:
    AssetManager() = default;
    ~AssetManager() = default;

    void loadAssets(filepath filePath);
    filepath getAssetPath(AssetId assetId);
};

#endif //ASSETMANAGER_H
