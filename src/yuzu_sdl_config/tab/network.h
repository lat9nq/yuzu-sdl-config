#pragma once

#include <vector>
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
    GtkMenuButton* menu_button_network_interface;
    GtkEntry* entry_network_interface;
    GtkMenu* menu_network_interface;

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

private:
    void BuildUi() override;

    Settings::Values& settings;
    std::vector<std::string> interfaces;
};

// Does not need `extern "C" G_MODULE_EXPORT` since we connect it manually
void on_menu_network_interface_item_activate(GtkMenuItem* self, gpointer user_data);
} // namespace YuzuSdlConfig
