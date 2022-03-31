#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <common/settings_input.h>

namespace Hid {
class Device {
public:
    explicit Device(int id_);
    ~Device();

    const std::string& GetName() const;
    const Settings::PlayerInput& GetDefaultLayout() const;
    const SDL_JoystickGUID& GetGuid() const;

private:
    void ParseMapping();
    void Map(const std::string& input_name, const char* device_button);

    const int id;
    SDL_Joystick* joystick;
    std::string name;
    const SDL_JoystickGUID guid;
    char* guid_str;
    char* sdl_mapping;

    //~ char leftx_type;
    //~ char lefty_type;
    int leftx_button;
    int lefty_button;
    //~ char rightx_type;
    //~ char righty_type;
    int rightx_button;
    int righty_button;

    Settings::PlayerInput default_layout;
};
} // namespace Hid
