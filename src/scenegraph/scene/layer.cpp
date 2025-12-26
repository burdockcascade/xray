#include "layer.hpp"

/** Create a CircleNode from an XML node.
 *
 * @param xmlNode The XML node containing circle attributes.
 * @return A shared pointer to the created CircleNode.
 */
std::shared_ptr<Node> LayerNode::Create(const pugi::xml_node& xmlNode) {
    auto triangleNode = std::make_shared<LayerNode>();

    // Camera ID
    triangleNode->cameraId = xmlNode.attribute("camera-id").as_string("");

    return triangleNode;
}

/** Render the CircleNode.
 *
 * @param assets The AssetManager for resource access (not used here).
 */
void LayerNode::Render(const AssetManager& assets) {
    Node::Render(assets);
}