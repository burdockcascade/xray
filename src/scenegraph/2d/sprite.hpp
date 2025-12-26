#pragma once
#include <pugixml.hpp>
#include <string>

#include "../node.hpp"
#include "../../asset_manager.hpp"

class SpriteNode : public Node {
public:
    SpriteNode() { type = NodeType::Sprite; }

    std::string textureId;

    static std::shared_ptr<Node> Create(const pugi::xml_node& xmlNode);
    void Render(const AssetManager& assets) override;
};