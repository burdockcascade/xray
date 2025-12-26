#include "line.hpp"
#include "../../utils.hpp"

/** Create a RectangleNode from an XML node.
 *
 * @param xmlNode The XML node containing rectangle attributes.
 * @return A shared pointer to the created RectangleNode.
 */
std::shared_ptr<Node> LineNode::Create(const pugi::xml_node& xmlNode) {
    auto lineNode = std::make_shared<LineNode>();

    // Start
    lineNode->start.x = xmlNode.attribute("x1").as_float(0.0f);
    lineNode->start.y = xmlNode.attribute("y1").as_float(0.0f);

    // End
    lineNode->end.x = xmlNode.attribute("x2").as_float(0.0f);
    lineNode->end.y = xmlNode.attribute("y2").as_float(0.0f);

    // Color
    lineNode->color = ParseColor(xmlNode.attribute("color").as_string("#FFFFFF"));

    // Line Thickness
    lineNode->lineThickness = xmlNode.attribute("stroke-width").as_int(1);

    return lineNode;
}

/** Render the RectangleNode.
 *
 * @param assets The AssetManager for resource access (not used here).
 */
void LineNode::Render(const AssetManager& assets) {
    const Vector2 p1 = {
        worldPosition.x + (start.x - 0.0f) * worldScale,
        worldPosition.y + (start.y - 0.0f) * worldScale
    };
    const Vector2 p2 = {
        worldPosition.x + (end.x - 0.0f) * worldScale,
        worldPosition.y + (end.y - 0.0f) * worldScale
    };
    DrawLineEx(p1, p2, static_cast<float>(lineThickness) * worldScale, color);
    Node::Render(assets);
}