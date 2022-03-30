#include <SDL2/SDL.h>
#include <common/settings.h>
#include "yuzu_sdl_config/tab/controls_player.glade.h"
#include "yuzu_sdl_config/tab/controls_player.h"

namespace YuzuSdlConfig {
TabControlsPlayer::TabControlsPlayer(Settings::Values& settings_, u8 id_)
    : settings{settings_}, id{id_} {
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
    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) != SDL_INIT_GAMECONTROLLER) {
        if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) {
            std::fprintf(stderr,
                         "error: failed to initialize SDL2 game controller sub system: %s\n",
                         SDL_GetError());
            return;
        }
    }

    const int num_joysticks = SDL_NumJoysticks();
    for (int i = 0; i < num_joysticks; i++) {
        SDL_Joystick* joystick = SDL_JoystickOpen(i);
        gtk_combo_box_text_append_text(combo_box_text_device, SDL_JoystickName(joystick));
        SDL_JoystickClose(joystick);
    }
}
} // namespace YuzuSdlConfig
