#pragma once

#include "Engine/Core/shellpch.h"

namespace Shell::Gamepad {

    enum class ButtonCodeEnum : uint16_t {
        // From glfw3.h
        ButtonA                         =  0,
        ButtonCross = ButtonA,
        ButtonB                         =  1,
        ButtonCircle = ButtonB,
        ButtonX                         =  2,
        ButtonSquare = ButtonX,
        ButtonY                         =  3,
        ButtonTriangle = ButtonY,
        ButtonLeftBumper                =  4,
        ButtonRightBumper               =  5,
        ButtonBack                      =  6,
        ButtonStart                     =  7,
        ButtonGuide                     =  8,
        ButtonLeftThumb                 =  9,
        ButtonRightThumb                = 10,
        ButtonDPadUp                    = 11,
        ButtonDPadRight                 = 12,
        ButtonDPadDown                  = 13,
        ButtonDPadLeft                  = 14,
    };

    enum class AxisCodeEnum : uint8_t {
        LeftX                           = 0,
        LeftY                           = 1,
        RightX                          = 2,
        RightY                          = 3,
        LeftTrigger                     = 4,
        RightTrigger                    = 5,
    };
}