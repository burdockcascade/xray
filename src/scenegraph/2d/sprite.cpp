#include "sprite.hpp"

/** Create a SpriteNode from an XML node.
 *
 * @param xmlNode The XML node containing sprite attributes.
 * @return A shared pointer to the created SpriteNode.
 */
std::shared_ptr<SceneNode> SpriteNode::Create(const pugi::xml_node& xmlNode) {
    auto spriteNode = std::make_shared<SpriteNode>();

    // Parse texture ID
    spriteNode->textureId = xmlNode.attribute("texture-id").as_string("");

    return spriteNode;
}

/** Render the SpriteNode.
 *
 * @param assets The AssetManager for resource access.
 */
void SpriteNode::Render(const AssetManager& assets) {
    if (const Texture2D tex = assets.GetTexture(textureId); tex.id != 0) {
        const Rectangle src = { 0, 0, static_cast<float>(tex.width), static_cast<float>(tex.height) };
        const Rectangle dst = { worldPosition.x, worldPosition.y, tex.width * worldScale, tex.height * worldScale };
        const Vector2 origin = { static_cast<float>(tex.width)/2.0f, static_cast<float>(tex.height)/2.0f };

        DrawTexturePro(tex, src, dst, origin, worldRotation, WHITE);
    }

    SceneNode::Render(assets);
}