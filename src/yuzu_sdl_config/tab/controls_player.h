#pragma once

#include <common/common_types.h>
#include <common/settings_input.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Hid {
class Hid;
}

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
enum class Direction {
    X,
    Y,
};

class TabControlsPlayer : public Tab {
public:
    explicit TabControlsPlayer(Settings::Values& settings_, u8 id_, Hid::Hid& hid_);
    ~TabControlsPlayer();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    void PopulateInputDeviceList();
    void UpdateAllButtons();

    void CopySelectedLayoutToBuffer(int index);

    GtkGrid* grid_controls_player;
    GtkComboBoxText* combo_box_text_type;
    GtkCheckButton* check_button_connected;
    GtkComboBoxText* combo_box_text_device;
    GtkButton* button_refresh;
    GtkButton* button_lstick_left;
    GtkButton* button_lstick_right;
    GtkButton* button_lstick_up;
    GtkButton* button_lstick_down;
    GtkButton* button_lstick;
    GtkButton* button_l;
    GtkButton* button_zl;
    GtkButton* button_sl;
    GtkButton* button_sr;
    GtkButton* button_r;
    GtkButton* button_zr;
    GtkButton* button_a;
    GtkButton* button_b;
    GtkButton* button_x;
    GtkButton* button_y;
    GtkButton* button_dleft;
    GtkButton* button_dright;
    GtkButton* button_dup;
    GtkButton* button_ddown;
    GtkButton* button_plus;
    GtkButton* button_minus;
    GtkButton* button_capture;
    GtkButton* button_home;
    GtkButton* button_rstick_left;
    GtkButton* button_rstick_right;
    GtkButton* button_rstick_up;
    GtkButton* button_rstick_down;
    GtkButton* button_rstick;

private:
    void BuildUi() override;

    Settings::Values& settings;
    const u8 id; // ID for guest controller
    Hid::Hid& hid;

    Settings::PlayerInput player_buffer;
};

std::string GetAxisString(Direction direction, const std::string& map_string);
std::string GetButtonString(const std::string& map_string);

extern "C" G_MODULE_EXPORT void on_combo_box_text_device_changed(GtkComboBox* self,
                                                                 gpointer user_data);
extern "C" G_MODULE_EXPORT void on_button_refresh_clicked(GtkButton* self, gpointer user_data);
} // namespace YuzuSdlConfig
