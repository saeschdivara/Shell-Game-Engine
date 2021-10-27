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
        std::string Content;

        Node(std::string name) : Name(std::move(name)) {}
        Node(std::string name, Attribute * attribute) : Name(std::move(name)) { Attributes.push_back(attribute); }
        Node(std::string name, std::string content) : Name(std::move(name)), Content(std::move(content)) {}
        Node(std::string name, Attribute * attribute, std::string content) :
            Name(std::move(name)), Content(std::move(content)) {
            Attributes.push_back(attribute);
        }
    };

    struct Tree {
        Node * Root;
    };

    inline Node& operator<<(Node & node, Attribute * attribute) {
        node.Attributes.push_back(attribute);
        return node;
    }

    inline Node& operator<<(Node & node1, Node & node2) {
        node1.Children.push_back(&node2);
        return node1;
    }

    inline Node& operator<<(Node & node1, Node * node2) {
        node1.Children.push_back(node2);
        return node1;
    }

    class Generator {
    public:
        std::string GenerateXmlString(Tree * tree);
        std::string GenerateXmlString(Node * node);
        std::string GenerateXmlString(std::vector<Node *> nodes);
        std::string GenerateXmlString(std::vector<Attribute *> attributes);
        std::string GenerateXmlString(Attribute * attribute);

    };

}

