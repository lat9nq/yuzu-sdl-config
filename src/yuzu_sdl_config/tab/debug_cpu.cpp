#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/debug_cpu.glade.h"
#include "yuzu_sdl_config/tab/debug_cpu.h"

namespace YuzuSdlConfig {
TabDebugCpu::TabDebugCpu(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabDebugCpu::~TabDebugCpu() {
    g_object_unref(box_debug_cpu);
}

void TabDebugCpu::UpdateUi() {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_page_tables),
                                 settings.cpuopt_page_tables.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_block_linking),
                                 settings.cpuopt_block_linking.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_return_stack_buffer),
                                 settings.cpuopt_return_stack_buffer.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_fast_dispatcher),
                                 settings.cpuopt_fast_dispatcher.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_context_elimination),
                                 settings.cpuopt_context_elimination.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_const_prop),
                                 settings.cpuopt_const_prop.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_misc_ir),
                                 settings.cpuopt_misc_ir.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_reduce_misalign_checks),
                                 settings.cpuopt_reduce_misalign_checks.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_fastmem),
                                 settings.cpuopt_fastmem.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_fastmem_exclusives),
                                 settings.cpuopt_fastmem_exclusives.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_recompile_exclusives),
                                 settings.cpuopt_recompile_exclusives.GetValue());
}

void TabDebugCpu::ApplyUiConfiguration() {
    settings.cpuopt_page_tables =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_page_tables));
    settings.cpuopt_block_linking =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_block_linking));
    settings.cpuopt_return_stack_buffer =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_return_stack_buffer));
    settings.cpuopt_fast_dispatcher =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_fast_dispatcher));
    settings.cpuopt_context_elimination =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_context_elimination));
    settings.cpuopt_const_prop =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_const_prop));
    settings.cpuopt_misc_ir =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_misc_ir));
    settings.cpuopt_reduce_misalign_checks =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_reduce_misalign_checks));
    settings.cpuopt_fastmem =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_fastmem));
    settings.cpuopt_fastmem_exclusives =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_fastmem_exclusives));
    settings.cpuopt_recompile_exclusives =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_cpuopt_recompile_exclusives));
}

GtkWidget* TabDebugCpu::GetParent() const {
    return GTK_WIDGET(box_debug_cpu);
}

void TabDebugCpu::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(debug_cpu_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_debug_cpu = GTK_BOX(gtk_builder_get_object(builder, "box_debug_cpu"));

    check_button_cpuopt_page_tables =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_page_tables"));
    check_button_cpuopt_block_linking =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_block_linking"));
    check_button_cpuopt_return_stack_buffer = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_return_stack_buffer"));
    check_button_cpuopt_fast_dispatcher =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_fast_dispatcher"));
    check_button_cpuopt_context_elimination = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_context_elimination"));
    check_button_cpuopt_const_prop =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_const_prop"));
    check_button_cpuopt_misc_ir =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_misc_ir"));
    check_button_cpuopt_reduce_misalign_checks = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_reduce_misalign_checks"));
    check_button_cpuopt_fastmem =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_fastmem"));
    check_button_cpuopt_fastmem_exclusives =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_cpuopt_fastmem_exclusives"));
    check_button_cpuopt_recompile_exclusives = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_cpuopt_recompile_exclusives"));

    g_object_ref(box_debug_cpu);
    g_object_unref(builder);
}

} // namespace YuzuSdlConfig
