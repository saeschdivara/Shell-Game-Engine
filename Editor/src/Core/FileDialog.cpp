#include "FileDialog.h"

#include <nfd.hpp>

namespace Shell::Editor {
    std::string FileDialog::PickFolder() {
        std::string result;

        NFD::Init();
        nfdchar_t *outPath;
        auto resultCode = NFD::PickFolder(outPath, std::filesystem::current_path().c_str());

        if (resultCode == nfdresult_t::NFD_OKAY) {
            result = std::string(outPath);
            NFD::FreePath(outPath);
        }

        return result;
    }

    std::string FileDialog::ChooseFile() {
        std::string result;

        NFD::Init();
        nfdchar_t *outPath;
        auto resultCode = NFD::OpenDialog(outPath, nullptr, 0, std::filesystem::current_path().c_str());

        if (resultCode == nfdresult_t::NFD_OKAY) {
            result = std::string(outPath);
            NFD::FreePath(outPath);
        }

        return result;
    }

    std::string FileDialog::SaveFile() {
        std::string result;

        NFD::Init();
        nfdchar_t *outPath;
        auto resultCode = NFD::SaveDialog(outPath, nullptr, 0, std::filesystem::current_path().c_str());

        if (resultCode == nfdresult_t::NFD_OKAY) {
            result = std::string(outPath);
            NFD::FreePath(outPath);
        }

        return result;
    }
}