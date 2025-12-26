#include "circle.hpp"
#include "../../utils.hpp"

/** Create a CircleNode from an XML node.
 *
 * @param xmlNode The XML node containing circle attributes.
 * @return A shared pointer to the created CircleNode.
 */
std::shared_ptr<Node> CircleNode::Create(const pugi::xml_node& xmlNode) {
    auto circleNode = std::make_shared<CircleNode>();

    // Radius
    circleNode->radius = xmlNode.attribute("radius").as_float(10.0f);

    // Color
    circleNode->color = ParseColor(xmlNode.attribute("color").as_string("#FFFFFF"));

    // filled
    circleNode->filled = xmlNode.attribute("filled").as_bool(true);

    return circleNode;
}

/** Render the CircleNode.
 *
 * @param assets The AssetManager for resource access (not used here).
 */
void CircleNode::Render(const AssetManager& assets) {
    if (filled) {
        DrawCircleV(worldPosition, radius * worldScale, color);
    } else {
        DrawCircleLines(static_cast<int>(worldPosition.x), static_cast<int>(worldPosition.y), radius * worldScale, color);
    }
    Node::Render(assets);
}