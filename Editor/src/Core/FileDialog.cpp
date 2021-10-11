#include "FileDialog.h"

#include <nfd.hpp>

namespace Shell::Editor {
    std::filesystem::path FileDialog::PickFolder() {
        std::filesystem::path result;

        NFD::Init();
        nfdnchar_t *outPath;
        auto resultCode = NFD::PickFolder(outPath, std::filesystem::current_path().c_str());

        if (resultCode == nfdresult_t::NFD_OKAY) {
            result = std::filesystem::absolute(outPath);
            NFD::FreePath(outPath);
        }

        return result;
    }

    std::filesystem::path FileDialog::ChooseFile() {
        std::filesystem::path result;

        NFD::Init();
        nfdnchar_t *outPath;
        auto resultCode = NFD::OpenDialog(outPath, nullptr, 0, std::filesystem::current_path().c_str());

        if (resultCode == nfdresult_t::NFD_OKAY) {
            result = std::filesystem::absolute(outPath);
            NFD::FreePath(outPath);
        }

        return result;
    }

    std::filesystem::path FileDialog::SaveFile() {
        std::filesystem::path result;

        NFD::Init();
        nfdnchar_t *outPath;
        auto resultCode = NFD::SaveDialog(outPath, nullptr, 0, std::filesystem::current_path().c_str());

        if (resultCode == nfdresult_t::NFD_OKAY) {
            result = std::filesystem::absolute(outPath);
            NFD::FreePath(outPath);
        }

        return result;
    }
}