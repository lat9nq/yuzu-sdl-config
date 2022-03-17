#include <cassert>
#include <cstring>
#include <common/common_types.h>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/general.glade.h"
#include "yuzu_sdl_config/tab/general.h"

namespace YuzuSdlConfig {
TabGeneral::TabGeneral(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}
TabGeneral::~TabGeneral() {
    g_object_unref(box_general);
}

void TabGeneral::BuildUi() {
    GtkBuilder* builder =
        gtk_builder_new_from_string(tab_general_configuration, strlen(tab_general_configuration));
    gtk_builder_connect_signals(builder, this);

    box_general = GTK_BOX(gtk_builder_get_object(builder, "box_general"));
    check_button_use_speed_limit =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_speed_limit"));
    check_button_use_extended_memory_layout = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_use_extended_memory_layout"));
    check_button_use_multi_core =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_multi_core"));
    spin_button_fps_cap = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fps_cap"));
    spin_button_speed_limit =
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_speed_limit"));

    g_object_ref(box_general);
    g_object_unref(builder);
}

void TabGeneral::UpdateUi() {
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_speed_limit),
                                 settings.use_speed_limit.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_extended_memory_layout),
                                 settings.use_extended_memory_layout.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_multi_core),
                                 settings.use_multi_core.GetValue());
    gtk_spin_button_set_value(spin_button_fps_cap, settings.fps_cap.GetValue());
    gtk_spin_button_set_value(spin_button_speed_limit, settings.speed_limit.GetValue());
}

void TabGeneral::ApplyUiConfiguration() {}

GtkWidget* TabGeneral::GetParent() const {
    return GTK_WIDGET(box_general);
}

void on_check_button_use_speed_limit_toggled(GtkToggleButton* self, gpointer user_data) {
    TabGeneral* tab_general = static_cast<TabGeneral*>(user_data);
    assert(tab_general->check_button_use_speed_limit == GTK_CHECK_BUTTON(self));

    gtk_widget_set_sensitive(GTK_WIDGET(tab_general->spin_button_speed_limit),
                             gtk_toggle_button_get_active(self));
}

} // namespace YuzuSdlConfig
