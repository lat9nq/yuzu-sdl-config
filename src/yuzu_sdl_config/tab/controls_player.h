#pragma once

#include <common/common_types.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabControlsPlayer : public Tab {
public:
    explicit TabControlsPlayer(Settings::Values& settings_, u8 id_);
    ~TabControlsPlayer();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    void PopulateInputDeviceList();

    GtkGrid* grid_controls_player;
    GtkComboBoxText* combo_box_text_type;
    GtkCheckButton* check_button_connected;
    GtkComboBoxText* combo_box_text_device;

private:
    void BuildUi() override;

    Settings::Values& settings;
    const u8 id;
};
} // namespace YuzuSdlConfig
