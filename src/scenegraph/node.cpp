#include "node.hpp"
#include "../asset_manager.hpp"
#include "raymath.h"

std::shared_ptr<Node> Node::Create(const pugi::xml_node& xmlNode) {
    return std::make_shared<Node>();
}

void Node::AddChild(const std::shared_ptr<Node>& child) {
    child->parent = this;
    children.push_back(child);
}

void Node::UpdateTransform() {
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

void Node::Render(const AssetManager& assets) {
    for (const auto& child : children) {
        child->Render(assets);
    }
}
