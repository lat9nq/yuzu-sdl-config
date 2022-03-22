#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <optional>
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

void TabSystem::UpdateUi() {
    const bool rng_seed_enable = settings.rng_seed.GetValue().has_value();
    const std::string rng_seed{std::to_string(settings.rng_seed.GetValue().value_or(0))};
    gtk_entry_set_text(entry_rng_seed, rng_seed.c_str());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_rng_seed_enable), rng_seed_enable);
    gtk_widget_set_sensitive(GTK_WIDGET(entry_rng_seed), rng_seed_enable);

    const std::time_t the_time = settings.custom_rtc.value_or(std::time(nullptr));
    const bool custom_rtc_enable = settings.custom_rtc.has_value();
    const std::string custom_rtc{std::to_string(the_time)};
    gtk_entry_set_text(entry_custom_rtc, custom_rtc.c_str());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_custom_rtc), custom_rtc_enable);
    gtk_widget_set_sensitive(GTK_WIDGET(entry_custom_rtc), custom_rtc_enable);
    gtk_widget_set_sensitive(GTK_WIDGET(calendar_custom_rtc), custom_rtc_enable);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_language_index),
                             settings.language_index.GetValue());
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_region_index),
                             settings.region_index.GetValue());
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_time_zone_index),
                             settings.time_zone_index.GetValue());
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_sound_index),
                             settings.sound_index.GetValue());
}

void TabSystem::ApplyUiConfiguration() {
    settings.language_index =
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_language_index));
    settings.region_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_region_index));
    settings.time_zone_index =
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_time_zone_index));
    settings.sound_index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_sound_index));

    const bool custom_rtc_enable =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_custom_rtc));
    settings.custom_rtc =
        custom_rtc_enable ? std::stol(gtk_entry_get_text(entry_custom_rtc)) : std::optional<s64>();

    const bool rng_seed_enable =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_rng_seed_enable));
    settings.rng_seed = rng_seed_enable
                            ? static_cast<u32>(std::stol(gtk_entry_get_text(entry_rng_seed)))
                            : std::optional<u32>();
}

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
    entry_custom_rtc = GTK_ENTRY(gtk_builder_get_object(builder, "entry_custom_rtc"));
    entry_buffer_rng_seed =
        GTK_ENTRY_BUFFER(gtk_builder_get_object(builder, "entry_buffer_rng_seed"));

    g_object_ref(popover_calendar);
    g_object_ref(box_system);
    g_object_unref(builder);
}

GtkWidget* TabSystem::GetParent() const {
    return GTK_WIDGET(box_system);
}

void on_entry_rng_seed_changed(GtkEditable* self, gpointer user_data) {
    TabSystem* tab_system = static_cast<TabSystem*>(user_data);
    assert(GTK_EDITABLE(tab_system->entry_rng_seed) == self);

    const std::string text{gtk_editable_get_chars(self, 0, -1)};
    std::string sanitized{};
    bool set{false}; // Recursive condition
    for (std::size_t i = 0; i < text.size(); i++) {
        if (std::isdigit(text[i])) {
            sanitized.push_back(text[i]);
        } else {
            set = true;
        }
    }
    // This signal handler is unnecessarily recursive, but I'm not aware of a way to change the text
    // without calling a function that signals this
    if (set) {
        gtk_entry_buffer_set_text(tab_system->entry_buffer_rng_seed, sanitized.c_str(), -1);
    }
}

void on_check_button_custom_rtc_toggled(GtkCheckButton* self, gpointer user_data) {
    TabSystem* tab_system = static_cast<TabSystem*>(user_data);
    assert(tab_system->check_button_custom_rtc == self);

    const bool sensitive = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self));
    gtk_widget_set_sensitive(GTK_WIDGET(tab_system->entry_custom_rtc), sensitive);
    gtk_widget_set_sensitive(GTK_WIDGET(tab_system->calendar_custom_rtc), sensitive);
}

void on_check_button_rng_seed_enable_toggled(GtkCheckButton* self, gpointer user_data) {
    TabSystem* tab_system = static_cast<TabSystem*>(user_data);
    assert(tab_system->check_button_rng_seed_enable == self);

    const bool sensitive = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self));
    gtk_widget_set_sensitive(GTK_WIDGET(tab_system->entry_rng_seed), sensitive);
}

void on_button_show_calendar_clicked(GtkButton* self, gpointer user_data) {
    TabSystem* tab_system = static_cast<TabSystem*>(user_data);
    assert(tab_system->button_show_calendar == self);

    gtk_widget_show(GTK_WIDGET(tab_system->popover_calendar));
}
} // namespace YuzuSdlConfig
