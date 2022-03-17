#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabDebug : public Tab {
public:
    explicit TabDebug(Settings::Values& settings_);
    ~TabDebug();

    GtkBox* box_debug;
    // Logging
    GtkEntry* entry_log_filter;
    GtkCheckButton* check_button_extended_logging;
    GtkButton* button_open_log_location;
    // Graphics
    GtkCheckButton* check_button_renderer_debug;
    GtkCheckButton* check_button_disable_macro_jit;
    GtkCheckButton* check_button_renderer_shader_feedback;
    GtkCheckButton* check_button_disable_shader_loop_safety_checks;
    GtkCheckButton* check_button_enable_nsight_aftermath;
    GtkCheckButton* check_button_dump_shaders;
    // Debugging
    GtkCheckButton* check_button_enable_fs_access_log;
    GtkCheckButton* check_button_reporting_services;
    // Advanced
    GtkCheckButton* check_button_quest_flag;
    GtkCheckButton* check_button_cpu_debug_mode;
    GtkCheckButton* check_button_enable_all_controllers;
    GtkCheckButton* check_button_use_debug_asserts;
    GtkCheckButton* check_button_use_auto_stub;

    void UpdateUi() override;
    GtkWidget* GetParent() const override;

private:
    void BuildUi() override;

    Settings::Values& settings;
};
} // namespace YuzuSdlConfig
