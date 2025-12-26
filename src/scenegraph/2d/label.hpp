#pragma once
#include <pugixml.hpp>
#include <string>

#include "../scene_node.hpp"
#include "../../asset_manager.hpp"

class LabelNode : public SceneNode {
public:
    LabelNode() { type = NodeType::Text; }

    std::string text;
    std::string fontId;
    int fontSize = 20;
    Color color = ::BLACK;

    static std::shared_ptr<SceneNode> Create(const pugi::xml_node& xmlNode);
    void Render(const AssetManager& assets) override;
};