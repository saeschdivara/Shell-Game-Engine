#pragma once

#include <Engine/Core/shellpch.h>

namespace Shell::Editor {

    class FileDialog {
    public:
        static std::filesystem::path PickFolder();
        static std::filesystem::path ChooseFile();
        static std::filesystem::path SaveFile();

    private:
        FileDialog() = default;
    };
}


