#include <cstring>
#include <common/settings.h>
#include "yuzu_sdl_config/tab/debug.glade.h"
#include "yuzu_sdl_config/tab/debug.h"

namespace YuzuSdlConfig {
TabDebug::TabDebug(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabDebug::~TabDebug() {
    g_object_unref(box_debug);
}

void TabDebug::BuildUi() {
    GtkBuilder* builder =
        gtk_builder_new_from_string(tab_debug_configuration, strlen(tab_debug_configuration));
    gtk_builder_connect_signals(builder, this);

    box_debug = GTK_BOX(gtk_builder_get_object(builder, "box_debug"));
    // Logging
    entry_log_filter = GTK_ENTRY(gtk_builder_get_object(builder, "entry_log_filter"));
    check_button_extended_logging =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_extended_logging"));
    button_open_log_location =
        GTK_BUTTON(gtk_builder_get_object(builder, "button_open_log_location"));
    // Graphics
    check_button_renderer_debug =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_renderer_debug"));
    check_button_disable_macro_jit =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_disable_macro_jit"));
    check_button_renderer_shader_feedback =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_renderer_shader_feedback"));
    check_button_enable_nsight_aftermath =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_enable_nsight_aftermath"));
    check_button_disable_shader_loop_safety_checks = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_disable_shader_loop_safety_checks"));
    check_button_dump_shaders =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_dump_shaders"));
    // Debugging
    check_button_enable_fs_access_log =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_enable_fs_access_log"));
    check_button_reporting_services =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_reporting_services"));
    // Advanced
    check_button_quest_flag =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_quest_flag"));
    check_button_cpu_debug_mode =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpu_debug_mode"));
    check_button_enable_all_controllers =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_enable_all_controllers"));
    check_button_use_debug_asserts =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_debug_asserts"));
    check_button_use_auto_stub =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_auto_stub"));

    g_object_ref(box_debug);
    g_object_unref(builder);
}

void TabDebug::UpdateUi() {
    // Logging
    gtk_entry_set_text(entry_log_filter, settings.log_filter.GetValue().c_str());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_extended_logging),
                                 settings.extended_logging.GetValue());
    // Graphics
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_renderer_debug),
                                 settings.renderer_debug.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_disable_macro_jit),
                                 settings.disable_macro_jit.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_renderer_shader_feedback),
                                 settings.renderer_shader_feedback.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_disable_shader_loop_safety_checks),
                                 settings.disable_shader_loop_safety_checks.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_enable_nsight_aftermath),
                                 settings.enable_nsight_aftermath.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_dump_shaders),
                                 settings.dump_shaders.GetValue());
    // Debugging
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_enable_fs_access_log),
                                 settings.enable_fs_access_log.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_reporting_services),
                                 settings.reporting_services.GetValue());
    // Advanced
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_quest_flag),
                                 settings.quest_flag.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpu_debug_mode),
                                 settings.cpu_debug_mode.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_enable_all_controllers),
                                 settings.enable_all_controllers.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_debug_asserts),
                                 settings.use_debug_asserts.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_auto_stub),
                                 settings.use_auto_stub.GetValue());
}

GtkWidget* TabDebug::GetParent() const {
    return GTK_WIDGET(box_debug);
}
} // namespace YuzuSdlConfig
