#include <cstdio>
#include <string>
#include <basicini/basicini.h>
#include <common/common_types.h>
#include <common/settings.h>
#include "yuzu_sdl_config/config.h"

template <>
void LoadSetting(const BasicIni& ini, const std::string& section,
                 Settings::BasicSetting<u16>& setting) {
    setting = static_cast<u16>(ini.Get<int>(section, setting.GetLabel(), setting.GetDefault()));
}

template <typename T>
void LoadSetting(const BasicIni& ini, const std::string& section,
                 Settings::BasicSetting<T>& setting) {
    setting = ini.Get(section, setting.GetLabel(), setting.GetDefault());
}

void LoadConfig(const BasicIni& ini, Settings::Values& settings) {
    // clang-format off

    // Core
    LoadSetting(ini, "Core", settings.use_extended_memory_layout);
    LoadSetting(ini, "Core", settings.use_multi_core);

    // CPU
    LoadSetting(ini, "CPU", settings.cpu_debug_mode);

    // Renderer
    LoadSetting(ini, "Renderer", settings.use_speed_limit);
    LoadSetting(ini, "Renderer", settings.fps_cap);
    LoadSetting(ini, "Renderer", settings.speed_limit);

    LoadSetting(ini, "Renderer", settings.renderer_debug);
    LoadSetting(ini, "Renderer", settings.renderer_shader_feedback);
    LoadSetting(ini, "Renderer", settings.enable_nsight_aftermath);
    LoadSetting(ini, "Renderer", settings.disable_shader_loop_safety_checks);

    // Debugging
    LoadSetting(ini, "Debugging", settings.extended_logging);
    LoadSetting(ini, "Debugging", settings.disable_macro_jit);
    LoadSetting(ini, "Debugging", settings.dump_shaders);
    LoadSetting(ini, "Debugging", settings.enable_fs_access_log);
    LoadSetting(ini, "Debugging", settings.reporting_services);

    LoadSetting(ini, "Debugging", settings.quest_flag);
    LoadSetting(ini, "Debugging", settings.enable_all_controllers);
    LoadSetting(ini, "Debugging", settings.use_debug_asserts);
    LoadSetting(ini, "Debugging", settings.use_auto_stub);

    // Miscellaneous
    LoadSetting(ini, "Miscellaneous", settings.log_filter);

    // clang-format on
}

void ApplySettings(BasicIni& ini, const Settings::Values& settings) {}
