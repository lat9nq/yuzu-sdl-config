#pragma once

#include <array>
#include <string>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabSystem : public Tab {
public:
    explicit TabSystem(Settings::Values& settings_);
    ~TabSystem();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    GtkBox* box_system;
    GtkEntry* entry_rng_seed;
    GtkComboBoxText* combo_box_text_language_index;
    GtkComboBoxText* combo_box_text_region_index;
    GtkComboBoxText* combo_box_text_time_zone_index;
    GtkComboBoxText* combo_box_text_sound_index;
    GtkCheckButton* check_button_rng_seed_enable;
    GtkCheckButton* check_button_custom_rtc;
    GtkButton* button_show_calendar;
    GtkCalendar* calendar_custom_rtc;
    GtkPopover* popover_calendar;
    GtkEntry* entry_custom_rtc;
    GtkEntryBuffer* entry_buffer_rng_seed;

private:
    void BuildUi() override;

    Settings::Values& settings;
};

extern "C" G_MODULE_EXPORT void on_entry_rng_seed_changed(GtkEditable* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_check_button_custom_rtc_toggled(GtkCheckButton* self,
                                                                   gpointer user_data);
extern "C" G_MODULE_EXPORT void on_check_button_rng_seed_enable_toggled(GtkCheckButton* self,
                                                                        gpointer user_data);
extern "C" G_MODULE_EXPORT void on_button_show_calendar_clicked(GtkButton* self,
                                                                gpointer user_data);
} // namespace YuzuSdlConfig
