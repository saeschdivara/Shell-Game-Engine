#include "VisualStudioProjectManager.h"

#include "Engine/Core/Profiling.h"
#include "Engine/Utils/Uuid.h"
#include "Engine/Utils/Xml.h"

#include <fstream>

namespace Shell::Scripting {
    void VisualStudioProjectManager::CreateProject(const std::filesystem::path &projectPath,
                                                   const std::string &projectName) {
        OPTICK_EVENT();

        auto solutionFilePath = projectPath / (projectName + ".sln");
        auto vsProjectFilePath = projectPath / (projectName + ".csproj");

        if (exists(solutionFilePath)) {
            return;
        }

        auto solutionUuid = Uuid::Create();
        auto projectUuid = Uuid::Create();

        auto projectUuidString = UuidToString(projectUuid);

        Xml::Node root("Project");
        root << new Xml::Attribute("ToolsVersion", "4.0")
             << new Xml::Attribute("DefaultTargets", "Build")
             << new Xml::Attribute("xmlns", "http://schemas.microsoft.com/developer/msbuild/2003");

        Xml::Node importNode("Import");
        importNode << new Xml::Attribute("Project", "$(MSBuildExtensionsPath)\\$(MSBuildToolsVersion)\\Microsoft.Common.props")
                   << new Xml::Attribute("Condition", "Exists('$(MSBuildExtensionsPath)\\$(MSBuildToolsVersion)\\Microsoft.Common.props')");

        Xml::Node propertyGroupNode("PropertyGroup");
        propertyGroupNode << new Xml::Node("Configuration", new Xml::Attribute("Condition", " '$(Configuration)' == '' "), "Debug")
                          << new Xml::Node("Platform", new Xml::Attribute("Condition", " '$(Platform)' == '' "), "AnyCPU")
                          << new Xml::Node("ProjectGuid", "{" + projectUuidString + "}")
                          << new Xml::Node("OutputType", "Library")
                          << new Xml::Node("AppDesignerFolder", "Properties")
                          << new Xml::Node("RootNamespace", "App")
                          << new Xml::Node("AssemblyName", "Custom-App")
                          << new Xml::Node("TargetFrameworkVersion", "v4.7.2")
                          << new Xml::Node("FileAlignment", "512");

        Xml::Node propertyGroupNodeDebug("PropertyGroup", new Xml::Attribute("Condition", " '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' "));
        propertyGroupNodeDebug << new Xml::Node("PlatformTarget", "AnyCPU")
                               << new Xml::Node("DebugSymbols", "true")
                               << new Xml::Node("DebugType", "full")
                               << new Xml::Node("Optimize", "false")
                               << new Xml::Node("OutputPath", "bin\\Debug\\")
                               << new Xml::Node("DefineConstants", "DEBUG;TRACE")
                               << new Xml::Node("ErrorReport", "prompt")
                               << new Xml::Node("WarningLevel", "4");

        Xml::Node propertyGroupNodeRelease("PropertyGroup", new Xml::Attribute("Condition", " '$(Configuration)|$(Platform)' == 'Release|AnyCPU' "));
        propertyGroupNodeRelease << new Xml::Node("PlatformTarget", "AnyCPU")
                           << new Xml::Node("DebugType", "pdbonly")
                           << new Xml::Node("Optimize", "true")
                           << new Xml::Node("OutputPath", "bin\\Release\\")
                           << new Xml::Node("DefineConstants", "TRACE")
                           << new Xml::Node("ErrorReport", "prompt")
                           << new Xml::Node("WarningLevel", "4");

        Xml::Node itemGroupInclude("ItemGroup");
        itemGroupInclude << new Xml::Node("Reference", new Xml::Attribute("Include", "System"))
                         << new Xml::Node("Reference", new Xml::Attribute("Include", "System.Core"))
                         << new Xml::Node("Reference", new Xml::Attribute("Include", "System.Data"))
                         << new Xml::Node("Reference", new Xml::Attribute("Include", "System.Xml"));

        Xml::Node importNode2("Import");
        importNode2 << new Xml::Attribute("Project", "$(MSBuildToolsPath)\\Microsoft.CSharp.targets");

        root << importNode;
        root << propertyGroupNode;
        root << propertyGroupNodeDebug;
        root << propertyGroupNodeRelease;
        root << itemGroupInclude;
        root << importNode2;

        Xml::Tree tree{};
        tree.Root = &root;

        Xml::Generator generator;

        auto xmlOutput = generator.GenerateXmlString(&tree);

        std::ofstream solutionFile(solutionFilePath);
        solutionFile << "\nMicrosoft Visual Studio Solution File, Format Version 12.00\n"
                     << "Project(\"{" << UuidToString(solutionUuid) << "}\") = \"" << projectName << "\", \"" << projectName << ".csproj\", \"{" << projectUuidString << "}\"\n"
                     << "EndProject\n"
                     << "Global\n"
                     << "\tGlobalSection(SolutionConfigurationPlatforms) = preSolution\n"
                     << "\t\tDebug|Any CPU = Debug|Any CPU\n"
                     << "\t\tRelease|Any CPU = Release|Any CPU\n"
                     << "\tEndGlobalSection\n"
                     << "\tGlobalSection(ProjectConfigurationPlatforms) = postSolution\n"
                     << "\t\t{" << projectUuidString << "}.Debug|Any CPU.ActiveCfg = Debug|Any CPU\n"
                     << "\t\t{" << projectUuidString << "}.Debug|Any CPU.Build.0 = Debug|Any CPU\n"
                     << "\t\t{" << projectUuidString << "}.Release|Any CPU.ActiveCfg = Release|Any CPU\n"
                     << "\t\t{" << projectUuidString << "}.Release|Any CPU.ActiveCfg = Release|Any CPU\n"
                     << "\tEndGlobalSection\n"
                     << "EndGlobal";

        std::ofstream projectFile(vsProjectFilePath);
        projectFile << xmlOutput;
    }
}
