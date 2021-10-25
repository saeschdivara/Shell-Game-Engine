#include <utility>

#pragma once

namespace Shell::Xml {

    struct Attribute {
        std::string Key;
        std::string Value;

        Attribute(std::string key, std::string  value) : Key(std::move(key)), Value(std::move(value)) {}
    };

    struct Node {
        std::string Name;
        std::vector<Attribute *> Attributes;
        std::vector<Node *> Children;
    };

    struct Tree {
        Node * Root;
    };

    class Generator {
    public:
        std::string GenerateXmlString(Tree * tree);
        std::string GenerateXmlString(Node * node);
        std::string GenerateXmlString(std::vector<Node *> nodes);
        std::string GenerateXmlString(std::vector<Attribute *> attributes);
        std::string GenerateXmlString(Attribute * attribute);

    };

}

