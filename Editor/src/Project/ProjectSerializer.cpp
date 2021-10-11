#include "ProjectSerializer.h"

#include <Engine/Core/EngineVersion.h>

#include <codecvt>
#include <fstream>
#include <yaml-cpp/emitter.h>

#define SHELL_ENGINE_EDITOR_VERSION "0.0.1"

namespace Shell {

    inline YAML::Emitter& operator<<(YAML::Emitter& emitter, ProjectSettings * settings) {

        emitter << YAML::BeginMap;

        emitter << YAML::Key << "Rendering";
        emitter << YAML::Value;

        emitter << YAML::Comment("This contains the info what render api is used for a particular operating system");
        emitter << YAML::BeginMap;
        for (const auto &[os, api]: settings->getOperatingSystemRenderer()) {
            emitter << YAML::Key << GetOperatingSystemName(os);
            emitter << YAML::Value << GetRenderApiName(api);
        }
        emitter << YAML::EndMap;

        emitter << YAML::EndMap;

        return emitter;
    }

    void ProjectSerializer::SerializeToFile(Project *project) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        YAML::Emitter out;
        out << YAML::Comment("This file is automatically generated by the editor, do not modify it!");
        out << YAML::BeginMap;
        out << YAML::Key << "Shell-Version";
        out << YAML::Value << SHELL_ENGINE_VERSION;
        out << YAML::Key << "Shell-Editor-Version";
        out << YAML::Value << SHELL_ENGINE_EDITOR_VERSION;
        out << YAML::Key << "Project-Name";
        out << YAML::Value << converter.to_bytes(project->GetName());

        out << YAML::Key << "Settings";
        out << YAML::Value << project->GetSettings();

        out << YAML::EndMap;

        auto projectFilePath = project->GetPath() / "project.yml";
        std::ofstream projectFile(projectFilePath);
        projectFile << out.c_str();
    }
}