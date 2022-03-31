#pragma once

#include <memory>
#include <vector>

namespace Hid {
class Device;

class Hid {
public:
    explicit Hid();
    ~Hid();

    const std::vector<std::unique_ptr<Device>>& GetDevices() const;

private:
    std::vector<std::unique_ptr<Device>> devices;
    int num_joysticks;
};
} // namespace Hid
