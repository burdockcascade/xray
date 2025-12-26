#pragma once
#include <pugixml.hpp>
#include <string>

#include "../scene_node.hpp"
#include "../../asset_manager.hpp"

class LineNode : public SceneNode {
public:
    LineNode() { type = NodeType::Shape; }

    Vector2 start = {0.0f, 0.0f};
    Vector2 end = {100.0f, 0.0f};
    Color color = ::WHITE;
    int lineThickness = 1;

    static std::shared_ptr<SceneNode> Create(const pugi::xml_node& xmlNode);
    void Render(const AssetManager& assets) override;
};