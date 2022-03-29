#include <cassert>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/cpu.glade.h"
#include "yuzu_sdl_config/tab/cpu.h"

namespace YuzuSdlConfig {
TabCpu::TabCpu(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabCpu::~TabCpu() {
    g_object_unref(box_cpu);
}

void TabCpu::UpdateUi() {
    const Settings::CPUAccuracy cpu_accuracy = settings.cpu_accuracy.GetValue();
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_cpu_accuracy),
                             static_cast<int>(cpu_accuracy));
    gtk_widget_set_visible(GTK_WIDGET(frame_unsafe_settings),
                           cpu_accuracy == Settings::CPUAccuracy::Unsafe);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_unfuse_fma),
                                 settings.cpuopt_unsafe_unfuse_fma.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_reduce_fp_error),
                                 settings.cpuopt_unsafe_reduce_fp_error.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_ignore_standard_fpcr),
                                 settings.cpuopt_unsafe_ignore_standard_fpcr.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_inaccurate_nan),
                                 settings.cpuopt_unsafe_inaccurate_nan.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_fastmem_check),
                                 settings.cpuopt_unsafe_fastmem_check.GetValue());
    gtk_toggle_button_set_active(
        GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_ignore_global_monitor),
        settings.cpuopt_unsafe_ignore_global_monitor.GetValue());
}

void TabCpu::ApplyUiConfiguration() {
    settings.cpu_accuracy = static_cast<Settings::CPUAccuracy>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_cpu_accuracy)));
    settings.cpuopt_unsafe_unfuse_fma =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_unfuse_fma));
    settings.cpuopt_unsafe_reduce_fp_error =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_reduce_fp_error));
    settings.cpuopt_unsafe_ignore_standard_fpcr = gtk_toggle_button_get_active(
        GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_ignore_standard_fpcr));
    settings.cpuopt_unsafe_inaccurate_nan =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_inaccurate_nan));
    settings.cpuopt_unsafe_fastmem_check =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_fastmem_check));
    settings.cpuopt_unsafe_ignore_global_monitor = gtk_toggle_button_get_active(
        GTK_TOGGLE_BUTTON(check_button_cpuopt_unsafe_ignore_global_monitor));
}

GtkWidget* TabCpu::GetParent() const {
    return GTK_WIDGET(box_cpu);
}

void TabCpu::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(cpu_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_cpu = GTK_BOX(gtk_builder_get_object(builder, "box_cpu"));
    combo_box_text_cpu_accuracy =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_cpu_accuracy"));
    frame_unsafe_settings =
        GTK_FRAME(GTK_FRAME(gtk_builder_get_object(builder, "frame_unsafe_settings")));
    check_button_cpuopt_unsafe_unfuse_fma =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_unsafe_unfuse_fma"));
    check_button_cpuopt_unsafe_reduce_fp_error = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_unsafe_reduce_fp_error"));
    check_button_cpuopt_unsafe_ignore_standard_fpcr = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_unsafe_ignore_standard_fpcr"));
    check_button_cpuopt_unsafe_inaccurate_nan = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_unsafe_inaccurate_nan"));
    check_button_cpuopt_unsafe_fastmem_check = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_unsafe_fastmem_check"));
    check_button_cpuopt_unsafe_ignore_global_monitor = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_unsafe_ignore_global_monitor"));

    g_object_ref(box_cpu);
    g_object_unref(builder);
}

void on_combo_box_text_cpu_accuracy_changed(GtkComboBox* self, gpointer user_data) {
    TabCpu* tab_cpu = static_cast<TabCpu*>(user_data);
    assert(GTK_COMBO_BOX(tab_cpu->combo_box_text_cpu_accuracy) == self);

    const Settings::CPUAccuracy index =
        static_cast<Settings::CPUAccuracy>(gtk_combo_box_get_active(self));
    const bool visible = (index == Settings::CPUAccuracy::Unsafe);
    gtk_widget_set_visible(GTK_WIDGET(tab_cpu->frame_unsafe_settings), visible);
}
} // namespace YuzuSdlConfig
