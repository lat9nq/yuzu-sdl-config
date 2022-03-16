#include <cassert>
#include <cstring>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab_general.glade.h"
#include "yuzu_sdl_config/tab_general.h"

namespace YuzuSdlConfig {
TabGeneral::TabGeneral(BasicIni& ini_) : ini{ini_} {
    BuildUi();
}
TabGeneral::~TabGeneral() = default;

void TabGeneral::BuildUi() {
    GtkBuilder* builder =
        gtk_builder_new_from_string(tab_general_configuration, strlen(tab_general_configuration));
    gtk_builder_connect_signals(builder, this);

    grid_general = GTK_GRID(gtk_builder_get_object(builder, "grid_general"));
    check_button_use_speed_limit =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_speed_limit"));
    check_button_use_extended_memory_layout = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_use_extended_memory_layout"));
    check_button_use_multi_core =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_multi_core"));
    spin_button_fps_cap = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fps_cap"));
    spin_button_speed_limit =
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_speed_limit"));

    g_object_ref(grid_general);
    g_object_unref(builder);
}

void TabGeneral::UpdateUi() {
    bool use_extended_memory_layout;
    bool use_multi_core;
    bool use_speed_limit;
    int fps_cap;
    int speed_limit;

    ini.Get("Core", "use_extended_memory_layout", use_extended_memory_layout, false);
    ini.Get("Core", "use_multi_core", use_multi_core, true);
    ini.Get("Renderer", "fps_cap", fps_cap, 1000);
    ini.Get("Renderer", "speed_limit", speed_limit, 100);
    ini.Get("Renderer", "use_speed_limit", use_speed_limit, true);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_speed_limit), use_speed_limit);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_extended_memory_layout),
                                 use_extended_memory_layout);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_multi_core), use_multi_core);
    gtk_spin_button_set_value(spin_button_fps_cap, fps_cap);
    gtk_spin_button_set_value(spin_button_speed_limit, speed_limit);
}

GtkWidget* TabGeneral::GetParent() {
    return GTK_WIDGET(grid_general);
}

void on_check_button_use_speed_limit_toggled(GtkToggleButton* self, gpointer user_data) {
    TabGeneral* tab_general = static_cast<TabGeneral*>(user_data);
    assert(tab_general->check_button_use_speed_limit == GTK_CHECK_BUTTON(self));

    gtk_widget_set_sensitive(GTK_WIDGET(tab_general->spin_button_speed_limit),
                             gtk_toggle_button_get_active(self));
}

} // namespace YuzuSdlConfig
