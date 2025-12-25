#pragma once
#include "config.hpp"
#include <filesystem>

constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;
const std::string DEFAULT_TITLE = "Default App";
constexpr int DEFAULT_FPS = 60;
constexpr bool DEFAULT_RESIZABLE = false;
constexpr bool DEFAULT_VSYNC = true;
constexpr bool DEFAULT_FULLSCREEN = false;
const std::string DEFAULT_BG_COLOR = "WHITE";

class config_loader {
public:
    static AppConfig Load(const std::filesystem::path& path);
};