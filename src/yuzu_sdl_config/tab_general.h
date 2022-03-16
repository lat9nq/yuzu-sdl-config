#pragma once

#include <basicini/basicini.h>
#include <gtk/gtk.h>

namespace YuzuSdlConfig {
class General {
public:
    explicit General(BasicIni& ini_);
    ~General();

    GtkGrid* grid_general;
    GtkCheckButton* check_button_use_speed_limit;
    GtkCheckButton* check_button_use_extended_memory_layout;
    GtkCheckButton* check_button_use_multi_core;
    GtkSpinButton* spin_button_fps_cap;
    GtkSpinButton* spin_button_speed_limit;

    void UpdateUi();

private:
    void BuildUi();

    BasicIni& ini;
};

extern "C" void on_check_button_use_speed_limit_toggled(GtkToggleButton* self, gpointer user_data);
} // namespace YuzuSdlConfig
