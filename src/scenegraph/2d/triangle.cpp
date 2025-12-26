#include "triangle.hpp"
#include "../../utils.hpp"

/** Create a CircleNode from an XML node.
 *
 * @param xmlNode The XML node containing circle attributes.
 * @return A shared pointer to the created CircleNode.
 */
std::shared_ptr<SceneNode> TriangleNode::Create(const pugi::xml_node& xmlNode) {
    auto triangleNode = std::make_shared<TriangleNode>();

    // x1, y1
    triangleNode->point1.x = xmlNode.attribute("x1").as_float(0.0f);
    triangleNode->point1.y = xmlNode.attribute("y1").as_float(0.0f);

    // x2, y2
    triangleNode->point2.x = xmlNode.attribute("x2").as_float(0.0f);
    triangleNode->point2.y = xmlNode.attribute("y2").as_float(0.0f);

    // x3, y3
    triangleNode->point3.x = xmlNode.attribute("x3").as_float(0.0f);
    triangleNode->point3.y = xmlNode.attribute("y3").as_float(0.0f);

    // filled
    triangleNode->filled = xmlNode.attribute("filled").as_bool(true);

    // Color
    triangleNode->color = ParseColor(xmlNode.attribute("color").as_string("#FFFFFF"));

    return triangleNode;
}

/** Render the CircleNode.
 *
 * @param assets The AssetManager for resource access (not used here).
 */
void TriangleNode::Render(const AssetManager& assets) {
    const Vector2 p1 = {
        worldPosition.x + (point1.x - 0.0f) * worldScale,
        worldPosition.y + (point1.y - 0.0f) * worldScale
    };
    const Vector2 p2 = {
        worldPosition.x + (point2.x - 0.0f) * worldScale,
        worldPosition.y + (point2.y - 0.0f) * worldScale
    };
    const Vector2 p3 = {
        worldPosition.x + (point3.x - 0.0f) * worldScale,
        worldPosition.y + (point3.y - 0.0f) * worldScale
    };
    if (filled) {
        DrawTriangle(p1, p2, p3, color);
    } else {
        DrawTriangleLines(p1, p2, p3, color);
    }
    SceneNode::Render(assets);
}