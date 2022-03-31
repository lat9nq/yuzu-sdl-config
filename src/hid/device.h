#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <common/input.h>

namespace Hid {
enum class InputType {
    Button,
    Axis,
};

struct Mapping {
    InputType type;
    int x;
    int y;
};

struct Layout {
    Mapping left;
    Mapping right;
    Mapping lstick;
    Mapping rstick;
    Mapping a;
    Mapping b;
    Mapping x;
    Mapping y;
    Mapping plus;
    Mapping minus;
    Mapping home;
    Mapping capture;
    Mapping dup;
    Mapping ddown;
    Mapping dleft;
    Mapping dright;
    Mapping l;
    Mapping r;
    Mapping zl;
    Mapping zr;
    Mapping sl;
    Mapping sr;
};

class Device {
public:
    explicit Device(int id_);
    ~Device();

    const std::string& GetName() const;
    const Layout& GetDefaultLayout() const;

private:
    void ParseMapping();
    void Map(const std::string& input_name, const char* device_button);

    const int id;
    SDL_Joystick* joystick;
    std::string name;
    const SDL_JoystickGUID guid;
    char* sdl_mapping;

    Layout default_layout;
};
} // namespace Hid
