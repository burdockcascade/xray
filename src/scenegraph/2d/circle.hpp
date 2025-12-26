#pragma once
#include <pugixml.hpp>
#include <string>

#include "../scene_node.hpp"
#include "../../asset_manager.hpp"

class CircleNode : public SceneNode {
public:
    CircleNode() { type = NodeType::Shape; }

    float radius = 10.0f;
    Color color = ::WHITE;
    bool filled = true;

    static std::shared_ptr<SceneNode> Create(const pugi::xml_node& xmlNode);
    void Render(const AssetManager& assets) override;
};