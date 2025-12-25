#include "engine.hpp"
#include "config_loader.hpp"
#include "CLI/CLI.hpp"
#include <filesystem>

#include "logger.hpp"

namespace fs = std::filesystem;

int main(const int argc, char* argv[]) {

    Log::Init();
    LOG_INFO("Engine Initialized");

    CLI::App cliApp{"App Engine v0.1"};

    std::string configPath = "config.xml";
    bool debugMode = false;

    // Add a flag to specify the config file
    cliApp.add_option("config_path", configPath, "Path to the XML configuration file")
        ->check(CLI::ExistingFile)
        ->required();

    cliApp.add_flag("-d,--debug", debugMode, "Enable debug logging");

    // Parse Arguments
    try {
        cliApp.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        // Handles --help, version, and parsing errors automatically
        return cliApp.exit(e);
    }

    if (debugMode) {
        Log::SetLevel(spdlog::level::debug);
        LOG_DEBUG("Debug Mode Enabled");
    }

    LOG_INFO("Loading configuration from: {}", fs::absolute(configPath).string());

    try {
        // Load Configuration (Logic separated in ConfigLoader)
        const AppConfig config = config_loader::Load(configPath);

        // Initialize and Run Engine
        Engine app(config);
        app.Run();

    } catch (const std::exception& e) {
        // Catch errors from XML parsing or Engine initialization
        LOG_CRITICAL("Fatal Error: {}", e.what());
        return -1;
    }

    return 0;
}