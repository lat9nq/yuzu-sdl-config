#pragma once

#include <basicini/basicini.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabGeneral : public Tab {
public:
    explicit TabGeneral(Settings::Values& values_);
    ~TabGeneral();

    GtkBox* box_general;
    GtkCheckButton* check_button_use_speed_limit;
    GtkCheckButton* check_button_use_extended_memory_layout;
    GtkCheckButton* check_button_use_multi_core;
    GtkSpinButton* spin_button_fps_cap;
    GtkSpinButton* spin_button_speed_limit;

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

private:
    void BuildUi() override;
    Settings::Values& settings;
};

extern "C" G_MODULE_EXPORT void on_check_button_use_speed_limit_toggled(GtkToggleButton* self,
                                                                        gpointer user_data);
} // namespace YuzuSdlConfig
