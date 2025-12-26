#include "label.hpp"
#include "../../utils.hpp"

/** Create a LabelNode from an XML node.
 *
 * @param xmlNode The XML node containing text attributes.
 * @return A shared pointer to the created LabelNode.
 */
std::shared_ptr<Node> LabelNode::Create(const pugi::xml_node& xmlNode) {
    auto textNode = std::make_shared<LabelNode>();

    // Text Content
    textNode->text = xmlNode.attribute("text").as_string("");

    // Font ID
    textNode->fontId = xmlNode.attribute("font-id").as_string("");

    // Font Size
    textNode->fontSize = xmlNode.attribute("font-size").as_int(20);

    // Color
    textNode->color = ParseColor(xmlNode.attribute("color").as_string("#000000"));

    return textNode;
}

/** Render the TextNode.
 *
 * @param assets The AssetManager for resource access.
 */
void LabelNode::Render(const AssetManager& assets) {
    // For simplicity, we will use the default font for now
    // Future: Load font from assets using fontId
    DrawText(text.c_str(), static_cast<int>(worldPosition.x), static_cast<int>(worldPosition.y), fontSize, color);

    Node::Render(assets);
}