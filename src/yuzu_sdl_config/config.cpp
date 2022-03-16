#include <string>
#include <basicini/basicini.h>
#include <common/common_types.h>
#include <common/settings.h>

void LoadConfig(BasicIni& ini, Settings::Values& settings) {
    // clang-format off

    // Core
    settings.use_extended_memory_layout = ini.Get("Core", "use_extended_memory_layout", settings.use_extended_memory_layout.GetDefault());
    settings.use_multi_core = ini.Get("Core", "use_multi_core", settings.use_multi_core.GetDefault());

    // Renderer
    settings.fps_cap = static_cast<u16>(ini.Get<int>("Renderer", "fps_cap", settings.fps_cap.GetDefault()));
    settings.speed_limit = static_cast<u16>(ini.Get<int>("Renderer", "speed_limit", settings.speed_limit.GetDefault()));
    settings.use_speed_limit = ini.Get("Renderer", "use_speed_limit", settings.use_speed_limit.GetDefault());

    // clang-format on
}

void ApplySettings(BasicIni& ini, Settings::Values& settings) {}
