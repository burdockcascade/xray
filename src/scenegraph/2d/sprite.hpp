#pragma once
#include <pugixml.hpp>
#include <string>

#include "../scene_node.hpp"
#include "../../asset_manager.hpp"

class SpriteNode : public SceneNode {
public:
    SpriteNode() { type = NodeType::Sprite; }

    std::string textureId;

    static std::shared_ptr<SceneNode> Create(const pugi::xml_node& xmlNode);
    void Render(const AssetManager& assets) override;
};