#pragma once

#include <gtk/gtk.h>

namespace YuzuSdlConfig {
class General {
public:
    explicit General();
    ~General();

    GtkGrid* grid_general;
    GtkCheckButton* check_button_use_speed_limit;
    GtkCheckButton* check_button_use_extended_memory_layout;
    GtkSpinButton* spin_button_fps_cap;
    GtkSpinButton* spin_button_speed_limit;

private:
    void BuildUi();
};

extern "C" void on_check_button_use_speed_limit_toggled(GtkToggleButton* self, gpointer user_data);
} // namespace YuzuSdlConfig
