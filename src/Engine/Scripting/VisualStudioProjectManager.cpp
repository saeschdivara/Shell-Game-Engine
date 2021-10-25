#include "VisualStudioProjectManager.h"

#include "Engine/Utils/Xml.h"

#include <fstream>

namespace Shell::Scripting {
    void VisualStudioProjectManager::CreateProject(const std::filesystem::path &projectPath,
                                                   const std::string &projectName) {

        auto solutionFilePath = projectPath / (projectName + ".sln");
        auto vsProjectFilePath = projectPath / (projectName + ".csproject");

        Xml::Tree tree{};

        Xml::Generator generator;

        auto xmlOutput = generator.GenerateXmlString(&tree);

        std::ofstream solutionFile(solutionFilePath);
        solutionFile << xmlOutput;
    }
}
