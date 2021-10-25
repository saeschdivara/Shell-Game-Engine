#include "Xml.h"

namespace Shell::Xml {
    std::string Generator::GenerateXmlString(Tree *tree) {
        return GenerateXmlString(tree->Root);
    }

    std::string Generator::GenerateXmlString(std::vector<Node *> nodes) {
        std::string output;
        for (const auto &node: nodes) {
            output += GenerateXmlString(node) + std::string("\n");
        }
        return output;
    }

    std::string Generator::GenerateXmlString(Node *node) {
        std::string output = std::string("<") + node->Name + " " + GenerateXmlString(node->Attributes) + std::string(">");
        output += GenerateXmlString(node->Children);
        output += std::string("</") + node->Name + std::string(">");

        return output;
    }

    std::string Generator::GenerateXmlString(std::vector<Attribute *> attributes) {
        std::string output;

        for (const auto &attribute: attributes) {
            output += GenerateXmlString(attribute) + " ";
        }

        return output;
    }

    std::string Generator::GenerateXmlString(Attribute *attribute) {
        return attribute->Key + "=\"" + attribute->Value + "\"";
    }
}