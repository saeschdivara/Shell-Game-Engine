#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell {

    enum class OperatingSystem : uint8_t {
        Unknown = 0x0,
        Windows = 0x1,
        Linux   = 0x2,
        MacOS   = 0x4
    };

    inline std::string GetOperatingSystemName(const OperatingSystem & os) {
        switch (os) {
            case OperatingSystem::Windows:
                return "Windows";
            case OperatingSystem::Linux:
                return "Linux";
            case OperatingSystem::MacOS:
                return "MacOS";

            case OperatingSystem::Unknown:
            default:
                return "Unknown";
        }
    }

    enum class RenderAPI : uint8_t {
        NoAPI      = 0x0,
        OpenGL     = 0x1,
        Vulkan     = 0x2,
        DirectX11  = 0x4,
        DirectX12  = 0x8,
        Metal      = 0xf,
    };

    inline std::string GetRenderApiName(const RenderAPI & api) {
        switch (api) {
            case RenderAPI::OpenGL:
                return "OpenGL";
            case RenderAPI::Vulkan:
                return "Vulkan";
            case RenderAPI::DirectX11:
                return "DirectX11";
            case RenderAPI::DirectX12:
                return "DirectX12";
            case RenderAPI::Metal:
                return "Metal";

            case RenderAPI::NoAPI:
            default:
                return "Unknown";
        }
    }
}