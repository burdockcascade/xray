#pragma once
#include <optional>
#include <string>
#include <vector>

#include "scenegraph/node.hpp"

enum class AssetType {
    Texture,
    Font,
    Sound,
    Unknown
};

struct AssetConfig {
    std::string id;
    std::string path;
    AssetType type = AssetType::Unknown;
};

struct WindowConfig {
    std::string title;
    int width;
    int height;
    int fps;
    bool resizable;
    bool fullscreen;
    bool vsync;
    Color bg_color;
};

struct SceneConfig {
    std::string name;
    std::vector<std::shared_ptr<Node>> rootNodes;
};

struct AppConfig {
    std::optional<WindowConfig> window = std::nullopt;
    std::vector<AssetConfig> assets;
    std::vector<SceneConfig> scenes;
};