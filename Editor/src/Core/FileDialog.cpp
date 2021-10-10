#include "FileDialog.h"

#include <nfd.hpp>

namespace Shell::Editor {
    std::string FileDialog::PickFolder() {
        std::string result;

        NFD::Init();
        nfdchar_t *outPath;
        NFD::PickFolder(outPath, std::filesystem::current_path().c_str());

        result = std::string(outPath);

        NFD::FreePath(outPath);

        return result;
    }

    std::string FileDialog::ChooseFile() {
        std::string result;

        NFD::Init();
        nfdchar_t *outPath;
        NFD::OpenDialog(outPath, nullptr, 0, std::filesystem::current_path().c_str());

        result = std::string(outPath);

        NFD::FreePath(outPath);

        return result;
    }

    std::string FileDialog::SaveFile() {
        std::string result;

        NFD::Init();
        nfdchar_t *outPath;
        NFD::SaveDialog(outPath, nullptr, 0, std::filesystem::current_path().c_str());

        result = std::string(outPath);

        NFD::FreePath(outPath);

        return result;
    }
}