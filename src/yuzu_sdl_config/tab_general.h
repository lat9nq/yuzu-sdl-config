#pragma once

#include <basicini/basicini.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab.h"

namespace YuzuSdlConfig {
class TabGeneral : public Tab {
public:
    explicit TabGeneral(BasicIni& ini_);
    ~TabGeneral();

    GtkGrid* grid_general;
    GtkCheckButton* check_button_use_speed_limit;
    GtkCheckButton* check_button_use_extended_memory_layout;
    GtkCheckButton* check_button_use_multi_core;
    GtkSpinButton* spin_button_fps_cap;
    GtkSpinButton* spin_button_speed_limit;

    void UpdateUi() override;
    GtkWidget* GetParent() override;

private:
    void BuildUi();

    BasicIni& ini;
};

extern "C" void on_check_button_use_speed_limit_toggled(GtkToggleButton* self, gpointer user_data);
} // namespace YuzuSdlConfig
