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
} // namespace Hid
