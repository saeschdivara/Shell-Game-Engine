#pragma once

#include <Engine/Core/shellpch.h>

namespace Shell::Editor {

    class FileDialog {
    public:
        static std::string PickFolder();
        static std::string ChooseFile();
        static std::string SaveFile();
    };
}


