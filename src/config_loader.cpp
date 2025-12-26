#include "config_loader.hpp"
#include <ranges>
#include <stdexcept>
#include "logger.hpp"
#include "scenegraph/scene_node.hpp"
#include "utils.hpp"
#include "scenegraph/2d/sprite.hpp"
#include "scenegraph/2d/label.hpp"

std::shared_ptr<SceneNode> ParseNode(pugi::xml_node xmlNode) {

    // 1. The Lookup Table
    // We make this 'static' so it is only created once when the program starts,
    // not every time the function runs.
    static const std::unordered_map<std::string_view, std::function<std::shared_ptr<SceneNode>(const pugi::xml_node&)>>
    nodeParsers = {
        {"node",   SceneNode::Create},
        {"sprite", SpriteNode::Create},
        {"label",   LabelNode::Create},
    };

    // 2. Lookup and Create
    const std::string_view tag = xmlNode.name();
    const auto it = nodeParsers.find(tag);

    if (it == nodeParsers.end()) {
        LOG_WARN("Unknown node type in XML: <{}>", tag);
        return nullptr;
    }

    // 4. Run the instruction we found (creates the specific node)
    std::shared_ptr<SceneNode> node = it->second(xmlNode);

    // 5. Apply Common Attributes (Transform, ID, etc.)
    // This runs for EVERY node type, so we keep it outside the map.
    node->id = xmlNode.attribute("id").as_string("unknown");
    node->localPosition.x = xmlNode.attribute("x").as_float(0.0f);
    node->localPosition.y = xmlNode.attribute("y").as_float(0.0f);
    node->localRotation = xmlNode.attribute("rotation").as_float(0.0f);
    node->localScale = xmlNode.attribute("scale").as_float(1.0f);

    // 6. Recursion: Check for children
    for (const pugi::xml_node child : xmlNode.children()) {
        if (auto childNode = ParseNode(child)) {
            node->AddChild(childNode);
        }
    }

    return node;
}

AppConfig config_loader::Load(const std::filesystem::path& path) {
    pugi::xml_document doc;

    // Load and parse the XML file
    if (const pugi::xml_parse_result result = doc.load_file(path.c_str()); !result) {
        throw std::runtime_error(std::string("XML Parse Error: ") + result.description());
    }

    // Navigate to root node
    const auto root = doc.child("application");
    if (!root) {
        throw std::runtime_error("Root node <application> not found");
    }

    AppConfig config;

    // Parse Window Configuration
    if (const auto windowNode = root.child("window")) {
        WindowConfig wCfg;
        
        wCfg.title = windowNode.attribute("title").as_string(DEFAULT_TITLE.c_str());
        wCfg.width = windowNode.attribute("width").as_int(DEFAULT_WIDTH);
        wCfg.height = windowNode.attribute("height").as_int(DEFAULT_HEIGHT);
        wCfg.fps = windowNode.attribute("fps").as_int(DEFAULT_FPS);
        wCfg.bg_color = ParseColor(windowNode.attribute("bg-color").as_string(DEFAULT_BG_COLOR.c_str()));

        // Parse Boolean Flags
        wCfg.resizable = windowNode.attribute("resizable").as_bool(DEFAULT_RESIZABLE);
        wCfg.fullscreen = windowNode.attribute("fullscreen").as_bool(DEFAULT_FULLSCREEN);
        wCfg.vsync = windowNode.attribute("vsync").as_bool(DEFAULT_VSYNC);
        
        config.window = wCfg;
    }

    // Parse Assets
    if (const auto assetsNode = root.child("assets")) {
        // Iterate over all <texture> nodes
        for (auto node : assetsNode.children("texture")) {
            AssetConfig asset;
            asset.id = node.attribute("id").as_string();
            asset.path = node.attribute("path").as_string();
            asset.type = AssetType::Texture;

            if (asset.id.empty() || asset.path.empty()) {
                LOG_WARN("Skipping invalid texture asset in XML (missing id or path)");
                continue;
            }

            config.assets.push_back(asset);
        }
    }

    // warn if no scenes
    if (!root.child("scenes")) {
        LOG_WARN("No <scenes> node found in configuration.");
    }

    if (auto scenesNode = root.child("scenes")) {
        for (auto sceneNode : scenesNode.children("scene")) {
            SceneConfig sceneCfg;
            sceneCfg.name = sceneNode.attribute("name").as_string("Untitled");

            // Iterate over all top-level nodes in this scene
            for (auto xmlChild : sceneNode.children()) {
                if (auto rootNode = ParseNode(xmlChild)) {
                    sceneCfg.rootNodes.push_back(rootNode);
                }
            }
            config.scenes.push_back(sceneCfg);
        }
    }

    return config;
}


