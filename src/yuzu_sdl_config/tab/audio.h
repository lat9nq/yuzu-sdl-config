#pragma once

#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabAudio : public Tab {
public:
    explicit TabAudio(Settings::Values& settings_);
    ~TabAudio();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    GtkBox* box_audio;
    GtkComboBoxText* combo_box_text_sink_id;
    GtkScale* scale_volume;
    GtkEntry* entry_audio_device_id;
    GtkMenuButton* menu_button_audio_device_id;
    GtkMenu* menu_audio_device_id;
    GtkAdjustment* adjustment_volume;

private:
    void BuildUi() override;
    void PopulateAudioDeviceList();

    Settings::Values& settings;
};

void on_menu_audio_device_id_item_activate(GtkMenuItem* self, gpointer user_data);
} // namespace YuzuSdlConfig
