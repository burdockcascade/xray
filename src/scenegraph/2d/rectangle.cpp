#include "rectangle.hpp"
#include "../../utils.hpp"

/** Create a RectangleNode from an XML node.
 *
 * @param xmlNode The XML node containing rectangle attributes.
 * @return A shared pointer to the created RectangleNode.
 */
std::shared_ptr<SceneNode> RectangleNode::Create(const pugi::xml_node& xmlNode) {
    auto rectNode = std::make_shared<RectangleNode>();

    // Width
    rectNode->width = xmlNode.attribute("width").as_float(20.0f);

    // Height
    rectNode->height = xmlNode.attribute("height").as_float(10.0f);

    // Color
    rectNode->color = ParseColor(xmlNode.attribute("color").as_string("#FFFFFF"));

    // Roundedness
    rectNode->cornerRadius = xmlNode.attribute("corner-radius").as_float(0.0f);

    // Corner Segments
    rectNode->cornerSegments = xmlNode.attribute("corner-segments").as_int(0);

    // filled
    rectNode->filled = xmlNode.attribute("filled").as_bool(true);

    // Line Thickness
    rectNode->lineThickness = xmlNode.attribute("line-thickness").as_int(1);

    return rectNode;
}

/** Render the RectangleNode.
 *
 * @param assets The AssetManager for resource access (not used here).
 */
void RectangleNode::Render(const AssetManager& assets) {
    const Rectangle rect = {
        worldPosition.x - (width * worldScale) / 2.0f,
        worldPosition.y - (height * worldScale) / 2.0f,
        width * worldScale,
        height * worldScale
    };

    if (filled) {
        if (cornerRadius > 0.0f) {
            DrawRectangleRounded(rect, cornerRadius, cornerSegments, color);
        } else {
            DrawRectangleRec(rect, color);
        }
    } else {
        if (cornerRadius > 0.0f) {
            DrawRectangleRoundedLines(rect, cornerRadius, cornerSegments, color);
        } else {
            DrawRectangleLinesEx(rect, lineThickness, color);
        }
    }

    SceneNode::Render(assets);
}