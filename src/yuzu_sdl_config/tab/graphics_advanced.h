#pragma once

#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabGraphicsAdvanced : public Tab {
public:
    explicit TabGraphicsAdvanced(Settings::Values& settings_);
    ~TabGraphicsAdvanced();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    GtkBox* box_graphics_advanced;
    GtkCheckButton* check_button_use_vsync;
    GtkCheckButton* check_button_use_asynchronous_shaders;
    GtkCheckButton* check_button_use_fast_gpu_time;
    GtkComboBoxText* combo_box_text_gpu_accuracy;
    GtkComboBoxText* combo_box_text_max_anisotropy;

private:
    void BuildUi() override;

    Settings::Values& settings;
};
} // namespace YuzuSdlConfig
