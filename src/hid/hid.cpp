#include <cstdio>
#include <vector>
#include "hid/device.h"
#include "hid/hid.h"

namespace Hid {
Hid::Hid() {
    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) != SDL_INIT_GAMECONTROLLER) {
        if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) {
            std::fprintf(stderr, "error: failed to initialize SDL Joystick subsystem: %s\n",
                         SDL_GetError());
            return;
        }
    }

    num_joysticks = SDL_NumJoysticks();

    for (int i = 0; i < num_joysticks; i++) {
        devices.push_back(std::make_unique<Device>(i));
    }
}

Hid::~Hid() {
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}

const std::vector<std::unique_ptr<Device>>& Hid::GetDevices() const {
    return devices;
}

void MakeButtonString(char* button_str, int button_str_len, char button_type, int button_value,
                      const char* guid_str) {
    const char* type = button_type == 'b' ? "button" : "axis";
    std::snprintf(button_str, button_str_len, "%s:%d,guid:%s,port:0,engine:sdl", type, button_value,
                  guid_str);
}
void MakeAnalogStickString(char* analog_str, int analog_str_len, int x_value, int y_value,
                           const char* guid_str) {
    std::snprintf(analog_str, analog_str_len,
                  "invert_y:+,invert_x:+,offset_y:0.000000,axis_x:%d,offset_x:-0.000000,axis_y:%d,"
                  "guid:%s,port:0,engine:sdl",
                  x_value, y_value, guid_str);
}

} // namespace Hid
