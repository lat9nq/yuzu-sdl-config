#include <array>
#include <cassert>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <common/settings.h>
#include "hid/device.h"
#include "hid/hid.h"
#include "yuzu_sdl_config/tab/controls_player.glade.h"
#include "yuzu_sdl_config/tab/controls_player.h"

namespace YuzuSdlConfig {

const std::string not_set{"[𝓃𝑜𝓉 𝓈𝑒𝓉]"};
constexpr std::array<const char*, 3> standard_devices = {"Any", "Keyboard Only", "Keyboard/Mouse"};

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
    combo_box_text_type =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_type"));
    check_button_connected =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_connected"));
    button_refresh = GTK_BUTTON(gtk_builder_get_object(builder, "button_refresh"));
    button_lstick_left = GTK_BUTTON(gtk_builder_get_object(builder, "button_lstick_left"));
    button_lstick_right = GTK_BUTTON(gtk_builder_get_object(builder, "button_lstick_right"));
    button_lstick_up = GTK_BUTTON(gtk_builder_get_object(builder, "button_lstick_up"));
    button_lstick_down = GTK_BUTTON(gtk_builder_get_object(builder, "button_lstick_down"));
    button_lstick = GTK_BUTTON(gtk_builder_get_object(builder, "button_lstick"));
    button_l = GTK_BUTTON(gtk_builder_get_object(builder, "button_l"));
    button_zl = GTK_BUTTON(gtk_builder_get_object(builder, "button_zl"));
    button_sl = GTK_BUTTON(gtk_builder_get_object(builder, "button_sl"));
    button_sr = GTK_BUTTON(gtk_builder_get_object(builder, "button_sr"));
    button_r = GTK_BUTTON(gtk_builder_get_object(builder, "button_r"));
    button_zr = GTK_BUTTON(gtk_builder_get_object(builder, "button_zr"));
    button_a = GTK_BUTTON(gtk_builder_get_object(builder, "button_a"));
    button_b = GTK_BUTTON(gtk_builder_get_object(builder, "button_b"));
    button_x = GTK_BUTTON(gtk_builder_get_object(builder, "button_x"));
    button_y = GTK_BUTTON(gtk_builder_get_object(builder, "button_y"));
    button_dleft = GTK_BUTTON(gtk_builder_get_object(builder, "button_dleft"));
    button_dright = GTK_BUTTON(gtk_builder_get_object(builder, "button_dright"));
    button_dup = GTK_BUTTON(gtk_builder_get_object(builder, "button_dup"));
    button_ddown = GTK_BUTTON(gtk_builder_get_object(builder, "button_ddown"));
    button_plus = GTK_BUTTON(gtk_builder_get_object(builder, "button_plus"));
    button_minus = GTK_BUTTON(gtk_builder_get_object(builder, "button_minus"));
    button_capture = GTK_BUTTON(gtk_builder_get_object(builder, "button_capture"));
    button_home = GTK_BUTTON(gtk_builder_get_object(builder, "button_home"));
    button_rstick_left = GTK_BUTTON(gtk_builder_get_object(builder, "button_rstick_left"));
    button_rstick_right = GTK_BUTTON(gtk_builder_get_object(builder, "button_rstick_right"));
    button_rstick_up = GTK_BUTTON(gtk_builder_get_object(builder, "button_rstick_up"));
    button_rstick_down = GTK_BUTTON(gtk_builder_get_object(builder, "button_rstick_down"));
    button_rstick = GTK_BUTTON(gtk_builder_get_object(builder, "button_rstick"));

    gtk_widget_set_name(GTK_WIDGET(grid_controls_player),
                        std::string{"ControlsP" + std::to_string(id)}.c_str());

    g_object_ref(grid_controls_player);
    g_object_unref(builder);
}

void TabControlsPlayer::UpdateUi() {
    auto& player = settings.players.GetValue()[id];
    const bool connected = player.connected;
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_connected), connected);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_type),
                             static_cast<int>(player.controller_type));
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_device), 0); // Device 'Any'

    player_buffer.buttons = player.buttons;
    player_buffer.analogs = player.analogs;
    UpdateAllButtons();
}

void TabControlsPlayer::ApplyUiConfiguration() {
    auto& player = settings.players.GetValue()[id];

    // TODO: Remove this
    const int absolute_device_index =
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_device));
    const int real_device_index = absolute_device_index - static_cast<int>(standard_devices.size());
    if (real_device_index > -1) {
        const Hid::Device& device = *hid.GetDevices()[real_device_index];
        player = device.GetDefaultLayout();
    }

    player.connected = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_connected));
    player.controller_type = static_cast<Settings::ControllerType>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_type)));
}

GtkWidget* TabControlsPlayer::GetParent() const {
    return GTK_WIDGET(grid_controls_player);
}

void TabControlsPlayer::PopulateInputDeviceList() {
    gtk_combo_box_text_remove_all(combo_box_text_device);

    for (const char* standard_device : standard_devices) {
        gtk_combo_box_text_append_text(combo_box_text_device, standard_device);
    }

    const auto& devices = hid.GetDevices();
    const std::size_t device_count = devices.size();

    for (std::size_t i = 0; i < device_count; i++) {
        const Hid::Device& device = *devices[i];
        gtk_combo_box_text_append_text(combo_box_text_device, device.GetName().c_str());
    }
}

void TabControlsPlayer::UpdateAllButtons() {
    //~ const auto& player = settings.players.GetValue()[id];
    const auto& player = player_buffer;

    gtk_button_set_label(
        button_lstick_left,
        GetAxisString(Direction::X, player.analogs[Settings::NativeAnalog::LStick]).c_str());
    gtk_button_set_label(
        button_lstick_right,
        GetAxisString(Direction::X, player.analogs[Settings::NativeAnalog::LStick]).c_str());
    gtk_button_set_label(
        button_lstick_up,
        GetAxisString(Direction::Y, player.analogs[Settings::NativeAnalog::LStick]).c_str());
    gtk_button_set_label(
        button_lstick_down,
        GetAxisString(Direction::Y, player.analogs[Settings::NativeAnalog::LStick]).c_str());
    gtk_button_set_label(
        button_rstick_left,
        GetAxisString(Direction::X, player.analogs[Settings::NativeAnalog::RStick]).c_str());
    gtk_button_set_label(
        button_rstick_right,
        GetAxisString(Direction::X, player.analogs[Settings::NativeAnalog::RStick]).c_str());
    gtk_button_set_label(
        button_rstick_up,
        GetAxisString(Direction::Y, player.analogs[Settings::NativeAnalog::RStick]).c_str());
    gtk_button_set_label(
        button_rstick_down,
        GetAxisString(Direction::Y, player.analogs[Settings::NativeAnalog::RStick]).c_str());
    gtk_button_set_label(button_lstick,
                         GetButtonString(player.buttons[Settings::NativeButton::LStick]).c_str());
    gtk_button_set_label(button_rstick,
                         GetButtonString(player.buttons[Settings::NativeButton::RStick]).c_str());
    gtk_button_set_label(button_l,
                         GetButtonString(player.buttons[Settings::NativeButton::L]).c_str());
    gtk_button_set_label(button_zl,
                         GetButtonString(player.buttons[Settings::NativeButton::ZL]).c_str());
    gtk_button_set_label(button_sl,
                         GetButtonString(player.buttons[Settings::NativeButton::SL]).c_str());
    gtk_button_set_label(button_sr,
                         GetButtonString(player.buttons[Settings::NativeButton::SR]).c_str());
    gtk_button_set_label(button_r,
                         GetButtonString(player.buttons[Settings::NativeButton::R]).c_str());
    gtk_button_set_label(button_zr,
                         GetButtonString(player.buttons[Settings::NativeButton::ZR]).c_str());
    gtk_button_set_label(button_a,
                         GetButtonString(player.buttons[Settings::NativeButton::A]).c_str());
    gtk_button_set_label(button_b,
                         GetButtonString(player.buttons[Settings::NativeButton::B]).c_str());
    gtk_button_set_label(button_x,
                         GetButtonString(player.buttons[Settings::NativeButton::X]).c_str());
    gtk_button_set_label(button_y,
                         GetButtonString(player.buttons[Settings::NativeButton::Y]).c_str());
    gtk_button_set_label(button_dleft,
                         GetButtonString(player.buttons[Settings::NativeButton::DLeft]).c_str());
    gtk_button_set_label(button_dright,
                         GetButtonString(player.buttons[Settings::NativeButton::DRight]).c_str());
    gtk_button_set_label(button_dup,
                         GetButtonString(player.buttons[Settings::NativeButton::DUp]).c_str());
    gtk_button_set_label(button_ddown,
                         GetButtonString(player.buttons[Settings::NativeButton::DDown]).c_str());
    gtk_button_set_label(button_plus,
                         GetButtonString(player.buttons[Settings::NativeButton::Plus]).c_str());
    gtk_button_set_label(button_minus,
                         GetButtonString(player.buttons[Settings::NativeButton::Minus]).c_str());
    gtk_button_set_label(button_home,
                         GetButtonString(player.buttons[Settings::NativeButton::Home]).c_str());
    gtk_button_set_label(
        button_capture,
        GetButtonString(player.buttons[Settings::NativeButton::Screenshot]).c_str());
}

void TabControlsPlayer::CopySelectedLayoutToBuffer(int index) {
    const auto& device = *hid.GetDevices()[index];
    const auto& layout = device.GetDefaultLayout();
    player_buffer.buttons = layout.buttons;
    player_buffer.analogs = layout.analogs;
}

std::string GetAxisString(Direction direction, const std::string& map_string) {
    if (map_string.empty()) {
        return not_set;
    }

    const char* search_string = direction == Direction::X ? "axis_x" : "axis_y";
    const std::size_t location_axis = map_string.find(search_string);
    if (location_axis == std::string::npos) {
        return not_set;
    }

    const std::size_t location_colon = map_string.find(':', location_axis);
    if (location_colon == std::string::npos) {
        return not_set;
    }

    const std::size_t location_comma = map_string.find(',', location_colon);

    std::size_t length = std::string::npos; // assume at end of string
    if (location_comma != std::string::npos) {
        length = location_comma - location_colon - 1;
    }

    return "Axis " + map_string.substr(location_colon + 1, length);
}

std::string GetButtonString(const std::string& map_string) {
    if (map_string.empty()) {
        return not_set;
    }

    const char* search_string_btn = "button";
    const char* search_string_axs = "axis";
    const std::size_t location_button = map_string.find(search_string_btn);
    const std::size_t location_axis = map_string.find(search_string_axs);
    const std::size_t location_type =
        location_button == std::string::npos ? location_axis : location_button;

    const std::string type = location_button == std::string::npos ? "Axis" : "Button";

    if (location_type == std::string::npos) {
        return not_set;
    }

    const std::size_t location_colon = map_string.find(':', location_type);
    if (location_colon == std::string::npos) {
        return not_set;
    }

    const std::size_t location_comma = map_string.find(',', location_colon);

    std::size_t length = std::string::npos; // assume at end of string
    if (location_comma != std::string::npos) {
        length = location_comma - location_colon - 1;
    }

    return type + " " + map_string.substr(location_colon + 1, length);
}

void on_combo_box_text_device_changed(GtkComboBox* self, gpointer user_data) {
    TabControlsPlayer* tab = static_cast<TabControlsPlayer*>(user_data);
    assert(tab->combo_box_text_device == GTK_COMBO_BOX_TEXT(self));

    const int index = gtk_combo_box_get_active(self) - static_cast<int>(standard_devices.size());
    if (index >= 0) {
        tab->CopySelectedLayoutToBuffer(index);
        tab->UpdateAllButtons();
    }
}
void on_button_refresh_clicked(GtkButton* self, gpointer user_data) {}
} // namespace YuzuSdlConfig
