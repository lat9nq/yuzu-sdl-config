#include <string>
#include <basicini/basicini.h>
#include <common/common_types.h>
#include <common/settings.h>
#include "yuzu_sdl_config/config.h"

template <typename T>
void LoadEnumSetting(const BasicIni& ini, const std::string& section,
                     Settings::BasicSetting<T>& setting) {
    setting = static_cast<T>(
        ini.Get<int>(section, setting.GetLabel(), static_cast<int>(setting.GetDefault())));
}

template <>
void LoadSetting(const BasicIni& ini, const std::string& section,
                 Settings::BasicSetting<u8>& setting) {
    setting = static_cast<u8>(ini.Get<int>(section, setting.GetLabel(), setting.GetDefault()));
}
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
    // Audio
    LoadSetting(ini, "Audio", settings.audio_device_id);
    LoadSetting(ini, "Audio", settings.sink_id);
    LoadSetting(ini, "Audio", settings.audio_muted);
    LoadSetting(ini, "Audio", settings.volume);

    // Core
    LoadSetting(ini, "Core", settings.use_extended_memory_layout);
    LoadSetting(ini, "Core", settings.use_multi_core);

    // CPU
    LoadEnumSetting(ini, "CPU", settings.cpu_accuracy);
    LoadSetting(ini, "CPU", settings.cpu_debug_mode);

    LoadSetting(ini, "CPU", settings.cpuopt_page_tables);
    LoadSetting(ini, "CPU", settings.cpuopt_block_linking);
    LoadSetting(ini, "CPU", settings.cpuopt_return_stack_buffer);
    LoadSetting(ini, "CPU", settings.cpuopt_fast_dispatcher);
    LoadSetting(ini, "CPU", settings.cpuopt_context_elimination);
    LoadSetting(ini, "CPU", settings.cpuopt_misc_ir);
    LoadSetting(ini, "CPU", settings.cpuopt_reduce_misalign_checks);
    LoadSetting(ini, "CPU", settings.cpuopt_fastmem);
    LoadSetting(ini, "CPU", settings.cpuopt_fastmem_exclusives);
    LoadSetting(ini, "CPU", settings.cpuopt_recompile_exclusives);

    LoadSetting(ini, "CPU", settings.cpuopt_unsafe_unfuse_fma);
    LoadSetting(ini, "CPU", settings.cpuopt_unsafe_reduce_fp_error);
    LoadSetting(ini, "CPU", settings.cpuopt_unsafe_ignore_standard_fpcr);
    LoadSetting(ini, "CPU", settings.cpuopt_unsafe_inaccurate_nan);
    LoadSetting(ini, "CPU", settings.cpuopt_unsafe_fastmem_check);
    LoadSetting(ini, "CPU", settings.cpuopt_unsafe_ignore_global_monitor);

    // Renderer
    LoadEnumSetting(ini, "Renderer", settings.renderer_backend);
    LoadSetting(ini, "Renderer", settings.vulkan_device);
    LoadEnumSetting(ini, "Renderer", settings.resolution_setup);
    LoadEnumSetting(ini, "Renderer", settings.scaling_filter);
    LoadEnumSetting(ini, "Renderer", settings.anti_aliasing);
    LoadEnumSetting(ini, "Renderer", settings.fullscreen_mode);
    LoadSetting(ini, "Renderer", settings.aspect_ratio);
    LoadSetting(ini, "Renderer", settings.max_anisotropy);
    LoadSetting(ini, "Renderer", settings.use_speed_limit);
    LoadSetting(ini, "Renderer", settings.speed_limit);
    LoadSetting(ini, "Renderer", settings.use_disk_shader_cache);
    LoadEnumSetting(ini, "Renderer", settings.gpu_accuracy);
    LoadSetting(ini, "Renderer", settings.use_asynchronous_gpu_emulation);
    LoadSetting(ini, "Renderer", settings.accelerate_astc);
    LoadSetting(ini, "Renderer", settings.use_vsync);
    LoadSetting(ini, "Renderer", settings.fps_cap);
    LoadSetting(ini, "Renderer", settings.disable_fps_limit);
    LoadEnumSetting(ini, "Renderer", settings.shader_backend);
    LoadSetting(ini, "Renderer", settings.use_asynchronous_shaders);
    LoadSetting(ini, "Renderer", settings.use_fast_gpu_time);
    LoadSetting(ini, "Renderer", settings.bg_red);
    LoadSetting(ini, "Renderer", settings.bg_green);
    LoadSetting(ini, "Renderer", settings.bg_blue);

    LoadSetting(ini, "Renderer", settings.renderer_debug);
    LoadSetting(ini, "Renderer", settings.renderer_shader_feedback);
    LoadSetting(ini, "Renderer", settings.enable_nsight_aftermath);
    LoadSetting(ini, "Renderer", settings.disable_shader_loop_safety_checks);

    // System
    const bool rng_seed_enabled = ini.Get("System", "rng_seed_enabled", false);
    if (rng_seed_enabled) {
        const u32 rng_seed = ini.Get("System", settings.rng_seed.GetLabel(), 0);
        settings.rng_seed = rng_seed;
    }
    const bool custom_rtc_enabled = ini.Get("System", "custom_rtc_enabled", false);
    if (custom_rtc_enabled) {
        const s64 custom_rtc = ini.Get("System", "custom_rtc", 0L);
        settings.custom_rtc = custom_rtc;
    }
    LoadSetting(ini, "System", settings.current_user);
    LoadSetting(ini, "System", settings.language_index);
    LoadSetting(ini, "System", settings.region_index);
    LoadSetting(ini, "System", settings.time_zone_index);
    LoadSetting(ini, "System", settings.sound_index);

    // Controls
    LoadSetting(ini, "ControlsGeneral", settings.use_docked_mode);
    LoadSetting(ini, "ControlsGeneral", settings.enable_raw_input);
    LoadSetting(ini, "ControlsGeneral", settings.controller_navigation);
    LoadSetting(ini, "ControlsGeneral", settings.vibration_enabled);
    LoadSetting(ini, "ControlsGeneral", settings.enable_accurate_vibrations);
    LoadSetting(ini, "ControlsGeneral", settings.motion_enabled);
    LoadSetting(ini, "ControlsGeneral", settings.udp_input_servers);
    LoadSetting(ini, "ControlsGeneral", settings.enable_udp_controller);
    LoadSetting(ini, "ControlsGeneral", settings.pause_tas_on_load);
    LoadSetting(ini, "ControlsGeneral", settings.tas_enable);
    LoadSetting(ini, "ControlsGeneral", settings.tas_loop);
    LoadSetting(ini, "ControlsGeneral", settings.mouse_panning);
    LoadSetting(ini, "ControlsGeneral", settings.mouse_panning_sensitivity);
    LoadSetting(ini, "ControlsGeneral", settings.mouse_enabled);
    LoadSetting(ini, "ControlsGeneral", settings.emulate_analog_keyboard);
    LoadSetting(ini, "ControlsGeneral", settings.keyboard_enabled);
    LoadSetting(ini, "ControlsGeneral", settings.debug_pad_enabled);
    LoadSetting(ini, "ControlsGeneral", settings.touch_device);
    LoadSetting(ini, "ControlsGeneral", settings.touch_from_button_map_index);

    // Data Storage
    LoadSetting(ini, "Data Storage", settings.use_virtual_sd);
    LoadSetting(ini, "Data Storage", settings.gamecard_inserted);
    LoadSetting(ini, "Data Storage", settings.gamecard_current_game);
    LoadSetting(ini, "Data Storage", settings.gamecard_path);

    // Debugging
    LoadSetting(ini, "Debugging", settings.use_gdbstub);
    LoadSetting(ini, "Debugging", settings.gdbstub_port);
    LoadSetting(ini, "Debugging", settings.program_args);
    LoadSetting(ini, "Debugging", settings.dump_exefs);
    LoadSetting(ini, "Debugging", settings.dump_nso);
    LoadSetting(ini, "Debugging", settings.dump_shaders);
    LoadSetting(ini, "Debugging", settings.enable_fs_access_log);
    LoadSetting(ini, "Debugging", settings.reporting_services);
    LoadSetting(ini, "Debugging", settings.quest_flag);
    LoadSetting(ini, "Debugging", settings.disable_macro_jit);
    LoadSetting(ini, "Debugging", settings.extended_logging);
    LoadSetting(ini, "Debugging", settings.use_debug_asserts);
    LoadSetting(ini, "Debugging", settings.use_auto_stub);
    LoadSetting(ini, "Debugging", settings.enable_all_controllers);

    // Miscellaneous
    LoadSetting(ini, "Miscellaneous", settings.log_filter);
    LoadSetting(ini, "Miscellaneous", settings.use_dev_keys);

    // Network
    LoadSetting(ini, "Network", settings.network_interface);

    // WebService
    LoadSetting(ini, "WebService", settings.enable_telemetry);
    LoadSetting(ini, "WebService", settings.web_api_url);
    LoadSetting(ini, "WebService", settings.yuzu_username);
    LoadSetting(ini, "WebService", settings.yuzu_token);
}

template <>
void ApplySetting(BasicIni& ini, const std::string& section,
                  const Settings::BasicSetting<std::string>& setting) {
    ini.Set(section, setting.GetLabel(), setting.GetValue());
}
template <>
void ApplySetting(BasicIni& ini, const std::string& section,
                  const Settings::BasicSetting<bool>& setting) {
    ini.Set(section, setting.GetLabel(), setting.GetValue() ? "true" : "false");
}
template <typename T>
void ApplySetting(BasicIni& ini, const std::string& section,
                  const Settings::BasicSetting<T>& setting) {
    ini.Set(section, setting.GetLabel(), std::to_string(setting.GetValue()));
}
template <typename T>
void ApplyEnumSetting(BasicIni& ini, const std::string& section,
                      const Settings::BasicSetting<T>& setting) {
    ini.Set(section, setting.GetLabel(), std::to_string(static_cast<u32>(setting.GetValue())));
}

void ApplySettings(BasicIni& ini, const Settings::Values& settings) {
    // Audio
    ApplySetting(ini, "Audio", settings.audio_device_id);
    ApplySetting(ini, "Audio", settings.sink_id);
    ApplySetting(ini, "Audio", settings.audio_muted);
    ApplySetting(ini, "Audio", settings.volume);

    // Core
    ApplySetting(ini, "Core", settings.use_multi_core);
    ApplySetting(ini, "Core", settings.use_extended_memory_layout);

    // CPU
    ApplyEnumSetting(ini, "CPU", settings.cpu_accuracy);
    ApplySetting(ini, "CPU", settings.cpu_debug_mode);
    ApplySetting(ini, "CPU", settings.cpuopt_page_tables);
    ApplySetting(ini, "CPU", settings.cpuopt_block_linking);
    ApplySetting(ini, "CPU", settings.cpuopt_return_stack_buffer);
    ApplySetting(ini, "CPU", settings.cpuopt_fast_dispatcher);
    ApplySetting(ini, "CPU", settings.cpuopt_context_elimination);
    ApplySetting(ini, "CPU", settings.cpuopt_misc_ir);
    ApplySetting(ini, "CPU", settings.cpuopt_reduce_misalign_checks);
    ApplySetting(ini, "CPU", settings.cpuopt_fastmem);
    ApplySetting(ini, "CPU", settings.cpuopt_fastmem_exclusives);
    ApplySetting(ini, "CPU", settings.cpuopt_recompile_exclusives);
    ApplySetting(ini, "CPU", settings.cpuopt_unsafe_unfuse_fma);
    ApplySetting(ini, "CPU", settings.cpuopt_unsafe_reduce_fp_error);
    ApplySetting(ini, "CPU", settings.cpuopt_unsafe_ignore_standard_fpcr);
    ApplySetting(ini, "CPU", settings.cpuopt_unsafe_inaccurate_nan);
    ApplySetting(ini, "CPU", settings.cpuopt_unsafe_fastmem_check);
    ApplySetting(ini, "CPU", settings.cpuopt_unsafe_ignore_global_monitor);

    // Renderer
    ApplyEnumSetting(ini, "Renderer", settings.renderer_backend);
    ApplySetting(ini, "Renderer", settings.vulkan_device);
    ApplyEnumSetting(ini, "Renderer", settings.resolution_setup);
    ApplyEnumSetting(ini, "Renderer", settings.scaling_filter);
    ApplyEnumSetting(ini, "Renderer", settings.anti_aliasing);
    ApplyEnumSetting(ini, "Renderer", settings.fullscreen_mode);
    ApplySetting(ini, "Renderer", settings.aspect_ratio);
    ApplySetting(ini, "Renderer", settings.max_anisotropy);
    ApplySetting(ini, "Renderer", settings.use_speed_limit);
    ApplySetting(ini, "Renderer", settings.speed_limit);
    ApplySetting(ini, "Renderer", settings.use_disk_shader_cache);
    ApplyEnumSetting(ini, "Renderer", settings.gpu_accuracy);
    ApplySetting(ini, "Renderer", settings.use_asynchronous_gpu_emulation);
    ApplySetting(ini, "Renderer", settings.accelerate_astc);
    ApplySetting(ini, "Renderer", settings.use_vsync);
    ApplySetting(ini, "Renderer", settings.fps_cap);
    ApplySetting(ini, "Renderer", settings.disable_fps_limit);
    ApplyEnumSetting(ini, "Renderer", settings.shader_backend);
    ApplySetting(ini, "Renderer", settings.use_asynchronous_shaders);
    ApplySetting(ini, "Renderer", settings.use_fast_gpu_time);
    ApplySetting(ini, "Renderer", settings.bg_red);
    ApplySetting(ini, "Renderer", settings.bg_green);
    ApplySetting(ini, "Renderer", settings.bg_blue);
    ApplySetting(ini, "Renderer", settings.renderer_debug);
    ApplySetting(ini, "Renderer", settings.renderer_shader_feedback);
    ApplySetting(ini, "Renderer", settings.enable_nsight_aftermath);
    ApplySetting(ini, "Renderer", settings.disable_shader_loop_safety_checks);

    // System
    const bool rng_seed_enabled = settings.rng_seed.GetValue().has_value();
    ini.Set("System", "rng_seed_enabled", std::to_string(rng_seed_enabled));
    if (rng_seed_enabled) {
        ini.Set("System", settings.rng_seed.GetLabel(),
                std::to_string(settings.rng_seed.GetValue().value()));
    }
    const bool custom_rtc_enabled = settings.custom_rtc.has_value();
    ini.Set("System", "custom_rtc_enabled", std::to_string(custom_rtc_enabled));
    if (custom_rtc_enabled) {
        ini.Set("System", "custom_rtc", std::to_string(settings.custom_rtc.value()));
    }
    ApplySetting(ini, "System", settings.current_user);
    ApplySetting(ini, "System", settings.language_index);
    ApplySetting(ini, "System", settings.region_index);
    ApplySetting(ini, "System", settings.time_zone_index);
    ApplySetting(ini, "System", settings.sound_index);

    // Controls
    ApplySetting(ini, "ControlsGeneral", settings.use_docked_mode);
    ApplySetting(ini, "ControlsGeneral", settings.enable_raw_input);
    ApplySetting(ini, "ControlsGeneral", settings.controller_navigation);
    ApplySetting(ini, "ControlsGeneral", settings.vibration_enabled);
    ApplySetting(ini, "ControlsGeneral", settings.enable_accurate_vibrations);
    ApplySetting(ini, "ControlsGeneral", settings.motion_enabled);
    ApplySetting(ini, "ControlsGeneral", settings.udp_input_servers);
    ApplySetting(ini, "ControlsGeneral", settings.enable_udp_controller);
    ApplySetting(ini, "ControlsGeneral", settings.pause_tas_on_load);
    ApplySetting(ini, "ControlsGeneral", settings.tas_enable);
    ApplySetting(ini, "ControlsGeneral", settings.tas_loop);
    ApplySetting(ini, "ControlsGeneral", settings.mouse_panning);
    ApplySetting(ini, "ControlsGeneral", settings.mouse_panning_sensitivity);
    ApplySetting(ini, "ControlsGeneral", settings.mouse_enabled);
    ApplySetting(ini, "ControlsGeneral", settings.emulate_analog_keyboard);
    ApplySetting(ini, "ControlsGeneral", settings.keyboard_enabled);
    ApplySetting(ini, "ControlsGeneral", settings.debug_pad_enabled);
    ApplySetting(ini, "ControlsGeneral", settings.touch_device);
    ApplySetting(ini, "ControlsGeneral", settings.touch_from_button_map_index);

    // Data Storage
    ApplySetting(ini, "Data Storage", settings.use_virtual_sd);
    ApplySetting(ini, "Data Storage", settings.gamecard_inserted);
    ApplySetting(ini, "Data Storage", settings.gamecard_current_game);
    ApplySetting(ini, "Data Storage", settings.gamecard_path);

    // Debugging
    ApplySetting(ini, "Debugging", settings.use_gdbstub);
    ApplySetting(ini, "Debugging", settings.gdbstub_port);
    ApplySetting(ini, "Debugging", settings.program_args);
    ApplySetting(ini, "Debugging", settings.dump_exefs);
    ApplySetting(ini, "Debugging", settings.dump_nso);
    ApplySetting(ini, "Debugging", settings.dump_shaders);
    ApplySetting(ini, "Debugging", settings.enable_fs_access_log);
    ApplySetting(ini, "Debugging", settings.reporting_services);
    ApplySetting(ini, "Debugging", settings.quest_flag);
    ApplySetting(ini, "Debugging", settings.disable_macro_jit);
    ApplySetting(ini, "Debugging", settings.extended_logging);
    ApplySetting(ini, "Debugging", settings.use_debug_asserts);
    ApplySetting(ini, "Debugging", settings.use_auto_stub);
    ApplySetting(ini, "Debugging", settings.enable_all_controllers);

    // Miscellaneous
    ApplySetting(ini, "Miscellaneous", settings.log_filter);
    ApplySetting(ini, "Miscellaneous", settings.use_dev_keys);

    // Network
    ApplySetting(ini, "Network", settings.network_interface);

    // WebService
    ApplySetting(ini, "WebService", settings.enable_telemetry);
    ApplySetting(ini, "WebService", settings.web_api_url);
    ApplySetting(ini, "WebService", settings.yuzu_username);
    ApplySetting(ini, "WebService", settings.yuzu_token);
}
