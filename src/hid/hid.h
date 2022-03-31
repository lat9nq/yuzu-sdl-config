#pragma once

#include <memory>
#include <vector>
#include <common/settings_input.h>

namespace Hid {
class Device;

constexpr std::array<const char*, Settings::NativeButton::NumButtons> button_strings{
    "button_a",      "button_b",     "button_x",     "button_y",    "button_lstick",
    "button_rstick", "button_l",     "button_r",     "button_zl",   "button_zr",
    "button_plus",   "button_minus", "button_dleft", "button_dup",  "button_dright",
    "button_ddown",  "button_sl",    "button_sr",    "button_home", "button_screenshot",
};

constexpr std::array<const char*, Settings::NativeAnalog::NumAnalogs> analog_strings{
    "lstick",
    "rstick",
};

class Hid {
public:
    explicit Hid();
    ~Hid();

    const std::vector<std::unique_ptr<Device>>& GetDevices() const;

private:
    std::vector<std::unique_ptr<Device>> devices;
    int num_joysticks;
};

void MakeButtonString(char* button_str, int button_str_len, char button_type, int button_value,
                      const char* guid_str);
void MakeAnalogStickString(char* analog_str, int analog_str_len, int x_value, int y_value,
                           const char* guid_str);
} // namespace Hid
