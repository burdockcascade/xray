#pragma once
#include <pugixml.hpp>
#include <string>

#include "../node.hpp"
#include "../../asset_manager.hpp"

class TriangleNode : public Node {
public:
    TriangleNode() { type = NodeType::Shape; }

    Vector2 point1 = {0.0f, 0.0f};
    Vector2 point2 = {20.0f, 0.0f};
    Vector2 point3 = {10.0f, 20.0f};
    Color color = ::WHITE;
    bool filled = true;

    static std::shared_ptr<Node> Create(const pugi::xml_node& xmlNode);
    void Render(const AssetManager& assets) override;
};