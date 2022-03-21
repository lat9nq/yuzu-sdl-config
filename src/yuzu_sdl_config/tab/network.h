#pragma once

#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabNetwork : public Tab {
public:
    TabNetwork(Settings::Values& settings_);
    ~TabNetwork();

    GtkBox* box_network;
    GtkComboBoxText* combo_box_text_network_interface;

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

private:
    void BuildUi() override;

    Settings::Values& settings;
};
} // namespace YuzuSdlConfig
