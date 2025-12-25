#include "scene_node.hpp"
#include "../asset_manager.hpp"
#include "raymath.h"

std::shared_ptr<SceneNode> SceneNode::Create(const pugi::xml_node& xmlNode) {
    return std::make_shared<SceneNode>();
}

void SceneNode::AddChild(const std::shared_ptr<SceneNode>& child) {
    child->parent = this;
    children.push_back(child);
}

void SceneNode::UpdateTransform() {
    if (parent) {
        worldScale = parent->worldScale * localScale;
        worldRotation = parent->worldRotation + localRotation;
        Vector2 rotatedOffset = ::Vector2Rotate(localPosition, parent->worldRotation * DEG2RAD);
        worldPosition = Vector2Add(parent->worldPosition, rotatedOffset);
    } else {
        worldPosition = localPosition;
        worldRotation = localRotation;
        worldScale = localScale;
    }

    for (const auto& child : children) {
        child->UpdateTransform();
    }
}

void SceneNode::Render(const AssetManager& assets) {
    for (const auto& child : children) {
        child->Render(assets);
    }
}
