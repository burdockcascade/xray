#include "engine.hpp"
#include "raylib.h"
#include "logger.hpp"

Engine::Engine(const AppConfig& config) : m_config(config) {

    // Initialize Window if Configured
    if (config.window) {
        const auto& w = *config.window;

        // Apply Window Flags based on Config
        if (w.resizable) {
            SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        }

        if (w.vsync) {
            SetConfigFlags(FLAG_VSYNC_HINT);
        }

        // Note: Fullscreen is often better handled *after* init or via specific logic,
        // but Raylib allows a flag if the resolution matches the monitor.
        // For safety, we will just open the window first.

        // Initialize
        InitWindow(w.width, w.height, w.title.c_str());

        // Set FPS
        SetTargetFPS(w.fps);

        // Handle Fullscreen overrides
        if (w.fullscreen) {
            // ToggleFullscreen() works better than the flag for ensuring desktop resolution context
            if (!IsWindowFullscreen()) ToggleFullscreen();
        }

        SetTargetFPS(w.fps);
    }

    // Load Assets
    for (const auto&[id, path, type] : config.assets) {
        if (type == AssetType::Texture) {
            m_assets.LoadTexture(id, path);
        }
    }

    // Load Scenes
    for (const auto& sceneCfg : config.scenes) {
        SceneNode scene;
        scene.id = sceneCfg.name;
        scene.children = sceneCfg.rootNodes;
        m_scenes.push_back(scene);
    }

}

Engine::~Engine() {
    CloseWindow();
}

void Engine::Run() const {
    while (!WindowShouldClose()) {
        Update();
        Render();
    }
}

void Engine::Update() {
    // Optional: Add a hotkey to toggle fullscreen at runtime
    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }
}

void Engine::Render() const {
    BeginDrawing();

    // set window
    if (m_config.window) {
        const Color bgColor = m_config.window->bg_color;
        ClearBackground(bgColor);
    }

    // Loop through scenes and render active one
    if (!m_scenes.empty()) {
        for (const auto& scene = m_scenes[m_activeSceneIndex]; const auto& rootNode : scene.children) {
            rootNode->UpdateTransform();
            rootNode->Render(m_assets);
        }
    }

    EndDrawing();
}
