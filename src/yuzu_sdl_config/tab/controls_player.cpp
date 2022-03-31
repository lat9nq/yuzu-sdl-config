#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <common/settings.h>
#include "hid/device.h"
#include "hid/hid.h"
#include "yuzu_sdl_config/tab/controls_player.glade.h"
#include "yuzu_sdl_config/tab/controls_player.h"

namespace YuzuSdlConfig {
TabControlsPlayer::TabControlsPlayer(Settings::Values& settings_, u8 id_, Hid::Hid& hid_)
    : settings{settings_}, id{id_}, hid{hid_} {
    BuildUi();
    PopulateInputDeviceList();
}

TabControlsPlayer::~TabControlsPlayer() {
    g_object_unref(grid_controls_player);
}

void TabControlsPlayer::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(controls_player_glade, -1);
    gtk_builder_connect_signals(builder, this);

    grid_controls_player = GTK_GRID(gtk_builder_get_object(builder, "grid_controls_player"));
    combo_box_text_device =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_device"));

    gtk_widget_set_name(GTK_WIDGET(grid_controls_player),
                        std::string{"ControlsP" + std::to_string(id)}.c_str());

    g_object_ref(grid_controls_player);
    g_object_unref(builder);
}

void TabControlsPlayer::UpdateUi() {}
void TabControlsPlayer::ApplyUiConfiguration() {}
GtkWidget* TabControlsPlayer::GetParent() const {
    return GTK_WIDGET(grid_controls_player);
}

void TabControlsPlayer::PopulateInputDeviceList() {
    const auto& devices = hid.GetDevices();
    const std::size_t device_count = devices.size();

    for (std::size_t i = 0; i < device_count; i++) {
        const Hid::Device& device = *devices[i];
        gtk_combo_box_text_append_text(combo_box_text_device, device.GetName().c_str());
    }
}
} // namespace YuzuSdlConfig
