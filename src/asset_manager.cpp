#include "asset_manager.hpp"

#include <ranges>

#include "logger.hpp"

AssetManager::~AssetManager() {
    UnloadAll();
}

void AssetManager::LoadTexture(const std::string& id, const std::string& path) {
    // 1. Check if already loaded
    if (m_textures.contains(id)) {
        LOG_WARN("Asset '{}' is already loaded. Skipping.", id);
        return;
    }

    // 2. Load from disk
    Texture2D tex = ::LoadTexture(path.c_str());

    // 3. Validation
    if (tex.id == 0) {
        LOG_ERROR("Failed to load texture '{}' from path: {}", id, path);
        return;
    }

    // 4. Store it
    m_textures[id] = tex;
    LOG_INFO("Loaded Texture: {} ({})", id, path);
}

Texture2D AssetManager::GetTexture(const std::string& id) const {
    // 1. Try to find the texture
    if (auto it = m_textures.find(id); it != m_textures.end()) {
        return it->second;
    }

    // 2. Not found? Log warning and return empty texture
    LOG_ERROR("Texture '{}' not found!", id);
    // Returning a default/empty texture structure prevents immediate segfaults,
    // though drawing it might just show nothing.
    return { 0 };
}

void AssetManager::UnloadAll() {
    for (const auto &texture: m_textures | std::views::values) {
        ::UnloadTexture(texture);
    }
    m_textures.clear();
    LOG_INFO("All assets unloaded.");
}