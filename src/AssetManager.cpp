#include "AssetManager.h"
#include <nlohmann/json.hpp>

void AssetManager::loadAssets(std::filesystem::path filePath) {
    nlohmann::json json = nlohmann::json::parse(filePath.string());

    /*
     * assets json file is structured like this:
     * {
     *     0: "...... (file path)",
     *     1: "...... (file path)",
     * }
     */

    for (const auto& [key, value] : json.items()) {
        AssetId assetId = static_cast<AssetId>(std::stoul(key));
        std::filesystem::path path = value.get<std::string>();
        assets[assetId] = path;
    }
}

std::filesystem::path AssetManager::getAssetPath(AssetId assetId) {
    return assets[assetId];
}