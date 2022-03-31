#include <cstdio>
#include <cstdlib>
#include <string>
#include <SDL2/SDL.h>
#include "hid/device.h"
#include "hid/hid.h"

using Buttons = Settings::NativeButton::Values;
using Analogs = Settings::NativeAnalog::Values;

namespace Hid {
Device::Device(int id_)
    : id{id_}, joystick{SDL_JoystickOpen(id)}, guid{SDL_JoystickGetGUID(joystick)},
      sdl_mapping{SDL_GameControllerMappingForGUID(guid)} {
    name = SDL_JoystickName(joystick);

    guid_str = new char[33];
    SDL_JoystickGetGUIDString(guid, guid_str, 33);

    ParseMapping();
}

Device::~Device() {
    SDL_free(sdl_mapping);
    delete guid_str;
}

const std::string& Device::GetName() const {
    return name;
}

const Settings::PlayerInput& Device::GetDefaultLayout() const {
    return default_layout;
}

const SDL_JoystickGUID& Device::GetGuid() const {
    return guid;
}

void Device::ParseMapping() {
    if (sdl_mapping == nullptr) {
        return;
    }

    std::string input_name;    // name of the button that we understand
    std::string device_button; // what button it is on the device
    std::string temp;
    for (int i = 0; sdl_mapping[i] != '\0'; i++) {
        switch (sdl_mapping[i]) {
        case ',':
            device_button = temp;
            temp.clear();

            Map(input_name, device_button.c_str());

            device_button.clear();
            input_name.clear();
            break;
        case ':':
            input_name = temp;
            temp.clear();
            break;
        default:
            temp.push_back(sdl_mapping[i]);
            break;
        }
        if (sdl_mapping[i + 1] == '\0') {
            Map(input_name, temp.c_str());
        }
    }

    char analog_str[255];
    MakeAnalogStickString(analog_str, 255, rightx_button, righty_button, guid_str);
    default_layout.analogs[Analogs::RStick] = analog_str;
    MakeAnalogStickString(analog_str, 255, leftx_button, lefty_button, guid_str);
    default_layout.analogs[Analogs::LStick] = analog_str;
}

void Device::Map(const std::string& input_name, const char* device_button) {
    if (input_name.empty()) {
        return;
    }

    const int button_value = std::atoi(device_button + 1);

    std::string* button{nullptr};
    if (input_name == "a") {
        button = &default_layout.buttons[Buttons::A];
    } else if (input_name == "b") {
        button = &default_layout.buttons[Buttons::B];
    } else if (input_name == "x") {
        button = &default_layout.buttons[Buttons::X];
    } else if (input_name == "y") {
        button = &default_layout.buttons[Buttons::Y];
    } else if (input_name == "back") {
        button = &default_layout.buttons[Buttons::Minus];
    } else if (input_name == "start") {
        button = &default_layout.buttons[Buttons::Plus];
    } else if (input_name == "dpdown") {
        button = &default_layout.buttons[Buttons::DDown];
    } else if (input_name == "dpleft") {
        button = &default_layout.buttons[Buttons::DLeft];
    } else if (input_name == "dpright") {
        button = &default_layout.buttons[Buttons::DRight];
    } else if (input_name == "dpup") {
        button = &default_layout.buttons[Buttons::DUp];
    } else if (input_name == "guide") {
        button = &default_layout.buttons[Buttons::Home];
    } else if (input_name == "leftshoulder") {
        button = &default_layout.buttons[Buttons::L];
    } else if (input_name == "leftstick") {
        button = &default_layout.buttons[Buttons::LStick];
    } else if (input_name == "lefttrigger") {
        button = &default_layout.buttons[Buttons::ZL];
    } else if (input_name == "rightshoulder") {
        button = &default_layout.buttons[Buttons::R];
    } else if (input_name == "rightstick") {
        button = &default_layout.buttons[Buttons::RStick];
    } else if (input_name == "righttrigger") {
        button = &default_layout.buttons[Buttons::ZR];
    } else if (input_name == "misc1") {
        button = &default_layout.buttons[Buttons::Screenshot];
    }

    if (button != nullptr) {
        char button_str[255];
        MakeButtonString(button_str, 255, device_button[0], button_value, guid_str);
        *button = button_str;
        return;
    }

    if (input_name == "leftx") {
        leftx_button = button_value;
    } else if (input_name == "lefty") {
        lefty_button = button_value;
    } else if (input_name == "rightx") {
        rightx_button = button_value;
    } else if (input_name == "righty") {
        righty_button = button_value;
    }
}
} // namespace Hid
