#pragma once
#include "asset_manager.hpp"
#include "config.hpp"

class Engine {
public:
    // Initialize the window and engine settings
    explicit Engine(const AppConfig& config);

    // Cleanup resources automatically
    ~Engine();

    // The main loop
    void Run() const;

private:
    AppConfig m_config;
    AssetManager m_assets;
    std::vector<Node> m_scenes;
    int m_activeSceneIndex = 0;

    // Update game logic
    static void Update();

    // Render the frame
    void Render() const;
};