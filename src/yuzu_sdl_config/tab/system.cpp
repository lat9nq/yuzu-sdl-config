#include <cassert>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/system.glade.h"
#include "yuzu_sdl_config/tab/system.h"
#include "yuzu_sdl_config/tab/tab.h"

namespace YuzuSdlConfig {
TabSystem::TabSystem(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}
TabSystem::~TabSystem() {
    g_object_unref(box_system);
    g_object_unref(popover_calendar);
}

void TabSystem::UpdateUi() {}

void TabSystem::ApplyUiConfiguration() {}

void TabSystem::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(system_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_system = GTK_BOX(gtk_builder_get_object(builder, "box_system"));
    entry_rng_seed = GTK_ENTRY(gtk_builder_get_object(builder, "entry_rng_seed"));
    combo_box_text_language_index =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_language_index"));
    combo_box_text_region_index =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_region_index"));
    combo_box_text_time_zone_index =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_time_zone_index"));
    combo_box_text_sound_index =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_sound_index"));
    check_button_rng_seed_enable =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_rng_seed_enable"));
    check_button_custom_rtc =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_custom_rtc"));
    button_show_calendar = GTK_BUTTON(gtk_builder_get_object(builder, "button_show_calendar"));
    calendar_custom_rtc = GTK_CALENDAR(gtk_builder_get_object(builder, "calendar_custom_rtc"));
    popover_calendar = GTK_POPOVER(gtk_builder_get_object(builder, "popover_calendar"));

    g_object_ref(popover_calendar);
    g_object_ref(box_system);
    g_object_unref(builder);
}

GtkWidget* TabSystem::GetParent() const {
    return GTK_WIDGET(box_system);
}

void on_check_button_custom_rtc_toggled(GtkCheckButton* self, gpointer user_data) {}
void on_check_button_rng_seed_enable_toggled(GtkCheckButton* self, gpointer user_data) {}
void on_button_show_calendar_clicked(GtkButton* self, gpointer user_data) {
    TabSystem* tab_system = static_cast<TabSystem*>(user_data);
    assert(tab_system->button_show_calendar == self);

    gtk_widget_show(GTK_WIDGET(tab_system->popover_calendar));
}
} // namespace YuzuSdlConfig
