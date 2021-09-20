#pragma once

#include "Engine/Core/InputService.h"

namespace Shell {

    class MacOSInputService : public InputService {
    protected:
        // keyboard
        bool IsKeyPressedImpl(Key::KeyCodeEnum code) override;

        // mouse
        bool IsMouseButtonPressedImpl(Mouse::MouseButtonEnum code) override;
        std::pair<float, float> GetMousePositionImpl() override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
    };
}


