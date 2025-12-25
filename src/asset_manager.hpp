#pragma once
#include "raylib.h"
#include <string>
#include <unordered_map>

class AssetManager {
public:
    // Lifecycle
    AssetManager() = default;
    ~AssetManager(); // Will unload all assets

    // Loading
    void LoadTexture(const std::string& id, const std::string& path);

    // Retrieval
    // Returns the requested texture, or a default one if not found
    Texture2D GetTexture(const std::string& id) const;

    // Cleanup (called by destructor automatically)
    void UnloadAll();

private:
    std::unordered_map<std::string, Texture2D> m_textures;
};