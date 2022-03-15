#include <cassert>
#include <cstring>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/general.glade.h"
#include "yuzu_sdl_config/general.h"

namespace YuzuSdlConfig {
General::General() {
    BuildUi();
}
General::~General() = default;

void General::BuildUi() {
    GtkBuilder* builder =
        gtk_builder_new_from_string(general_configuration, strlen(general_configuration));
    gtk_builder_connect_signals(builder, this);

    grid_general = GTK_GRID(gtk_builder_get_object(builder, "grid_general"));
    check_button_use_speed_limit =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_speed_limit"));
    check_button_use_extended_memory_layout = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_use_extended_memory_layout"));
    spin_button_fps_cap = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fps_cap"));
    spin_button_speed_limit =
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_speed_limit"));

    g_object_ref(grid_general);
    g_object_unref(builder);
}

void on_check_button_use_speed_limit_toggled(GtkToggleButton* self, gpointer user_data) {
    General* page_general = static_cast<General*>(user_data);
    assert(page_general->check_button_use_speed_limit == GTK_CHECK_BUTTON(self));

    gtk_widget_set_sensitive(GTK_WIDGET(page_general->spin_button_speed_limit),
                             gtk_toggle_button_get_active(self));
}

} // namespace YuzuSdlConfig
