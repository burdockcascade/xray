#pragma once
#include <pugixml.hpp>
#include <string>

#include "../scene_node.hpp"
#include "../../asset_manager.hpp"

class RectangleNode : public SceneNode {
public:
    RectangleNode() { type = NodeType::Shape; }

    float width = 20.0f;
    float height = 10.0f;
    Color color = ::WHITE;
    float cornerRadius = 0.0f;
    float cornerSegments = 0.0f;
    bool filled = true;
    int lineThickness = 1;

    static std::shared_ptr<SceneNode> Create(const pugi::xml_node& xmlNode);
    void Render(const AssetManager& assets) override;
};