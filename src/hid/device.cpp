#include <cstdlib>
#include <string>
#include <SDL2/SDL.h>
#include "hid/device.h"

namespace Hid {
Device::Device(int id_)
    : id{id_}, joystick{SDL_JoystickOpen(id)}, guid{SDL_JoystickGetGUID(joystick)},
      sdl_mapping{SDL_GameControllerMappingForGUID(guid)} {
    name = SDL_JoystickName(joystick);

    ParseMapping();
}

Device::~Device() {
    SDL_free(sdl_mapping);
}

const std::string& Device::GetName() const {
    return name;
}

const Layout& Device::GetDefaultLayout() const {
    return default_layout;
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
}

void Device::Map(const std::string& input_name, const char* device_button) {
    if (input_name.empty()) {
        return;
    }

    const int button_value = std::atoi(device_button + 1);
    Mapping* button{nullptr};
    if (input_name == "a") {
        button = &default_layout.a;
    } else if (input_name == "b") {
        button = &default_layout.b;
    } else if (input_name == "x") {
        button = &default_layout.x;
    } else if (input_name == "y") {
        button = &default_layout.y;
    } else if (input_name == "back") {
        button = &default_layout.minus;
    } else if (input_name == "start") {
        button = &default_layout.plus;
    } else if (input_name == "dpdown") {
        button = &default_layout.ddown;
    } else if (input_name == "dpleft") {
        button = &default_layout.dleft;
    } else if (input_name == "dpright") {
        button = &default_layout.dright;
    } else if (input_name == "dpup") {
        button = &default_layout.dup;
    } else if (input_name == "guide") {
        button = &default_layout.home;
    } else if (input_name == "leftshoulder") {
        button = &default_layout.l;
    } else if (input_name == "leftstick") {
        button = &default_layout.lstick;
    } else if (input_name == "lefttrigger") {
        button = &default_layout.zl;
    } else if (input_name == "rightshoulder") {
        button = &default_layout.r;
    } else if (input_name == "rightstick") {
        button = &default_layout.rstick;
    } else if (input_name == "righttrigger") {
        button = &default_layout.zr;
    } else if (input_name == "misc1") {
        button = &default_layout.capture;
    }

    if (button != nullptr) {
        button->x = button_value;
        button->type = device_button[0] == 'b' ? InputType::Button : InputType::Axis;
        return;
    }

    if (input_name == "leftx") {
        default_layout.left.x = button_value;
        default_layout.left.type = device_button[0] == 'b' ? InputType::Button : InputType::Axis;
    } else if (input_name == "lefty") {
        default_layout.left.y = button_value;
        default_layout.left.type = device_button[0] == 'b' ? InputType::Button : InputType::Axis;
    } else if (input_name == "rightx") {
        default_layout.right.x = button_value;
        default_layout.right.type = device_button[0] == 'b' ? InputType::Button : InputType::Axis;
    } else if (input_name == "righty") {
        default_layout.right.y = button_value;
        default_layout.right.type = device_button[0] == 'b' ? InputType::Button : InputType::Axis;
    }
}
} // namespace Hid
