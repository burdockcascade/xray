#pragma once
#include "raylib.h"
#include "raymath.h" // Needed for vector math
#include <string>
#include <vector>
#include <memory>
#include <pugixml.hpp>

#include "../asset_manager.hpp"

enum class NodeType {
    Base,
    Sprite,
    Text,
    Shape,
    Camera,
    Layer,
};

class Node {
public:
    virtual ~Node() = default;

    std::string id;
    NodeType type = NodeType::Base;

    // Transform Data
    Vector2 localPosition = {0.0f, 0.0f};
    float localRotation = 0.0f;
    float localScale = 1.0f;

    // Computed World Data
    Vector2 worldPosition = {0.0f, 0.0f};
    float worldRotation = 0.0f;
    float worldScale = 1.0f;

    // Hierarchy
    Node* parent = nullptr;
    std::vector<std::shared_ptr<Node>> children;

    // Core Methods
    void AddChild(const std::shared_ptr<Node>& child);
    void UpdateTransform();

    // Static Create Method: Creates a basic SceneNode from XML
    static std::shared_ptr<Node> Create(const pugi::xml_node& xmlNode);

    // Virtual Render: Base node draws nothing, but children might
    virtual void Render(const AssetManager& assets);
};