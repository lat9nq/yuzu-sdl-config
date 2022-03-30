#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/audio.glade.h"
#include "yuzu_sdl_config/tab/audio.h"

namespace YuzuSdlConfig {

const std::array<const char*, 4> sinks = {"auto", "cubeb", "sdl2", "null"};

TabAudio::TabAudio(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
    PopulateAudioDeviceList();
}

TabAudio::~TabAudio() {
    g_object_unref(box_audio);
}

void TabAudio::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(audio_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_audio = GTK_BOX(gtk_builder_get_object(builder, "box_audio"));
    combo_box_text_sink_id =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_sink_id"));
    scale_volume = GTK_SCALE(gtk_builder_get_object(builder, "scale_volume"));
    entry_audio_device_id = GTK_ENTRY(gtk_builder_get_object(builder, "entry_audio_device_id"));
    menu_button_audio_device_id =
        GTK_MENU_BUTTON(gtk_builder_get_object(builder, "menu_button_audio_device_id"));
    menu_audio_device_id = GTK_MENU(gtk_builder_get_object(builder, "menu_audio_device_id"));
    adjustment_volume = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_volume"));

    g_object_ref(box_audio);
    g_object_unref(builder);

    gtk_widget_set_halign(GTK_WIDGET(menu_audio_device_id), GTK_ALIGN_END);
}

void TabAudio::UpdateUi() {
    u32 sink_id{0};
    for (u32 i = 0; i < sinks.size(); i++) {
        if (settings.sink_id.GetValue() == sinks[i]) {
            sink_id = i;
            break;
        }
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_sink_id), sink_id);
    gtk_entry_set_text(entry_audio_device_id, settings.audio_device_id.GetValue().c_str());
    gtk_adjustment_set_value(adjustment_volume, settings.volume.GetValue());
}

void TabAudio::ApplyUiConfiguration() {
    settings.sink_id = sinks[gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_sink_id))];
    settings.audio_device_id = gtk_entry_get_text(entry_audio_device_id);
    settings.volume = static_cast<u8>(gtk_adjustment_get_value(adjustment_volume));
}

void TabAudio::PopulateAudioDeviceList() {
    std::vector<std::string> audio_devices;
    audio_devices.push_back("auto");

    for (auto device : audio_devices) {
        GtkWidget* menu_item = gtk_menu_item_new_with_label(device.c_str());
        gtk_widget_show(menu_item);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_audio_device_id), menu_item);

        g_signal_connect(G_OBJECT(menu_item), "activate",
                         G_CALLBACK(on_menu_audio_device_id_item_activate), this);
    }
}

GtkWidget* TabAudio::GetParent() const {
    return GTK_WIDGET(box_audio);
}

void on_menu_audio_device_id_item_activate(GtkMenuItem* self, gpointer user_data) {
    TabAudio* tab_audio = static_cast<TabAudio*>(user_data);

    const char* label = gtk_menu_item_get_label(self);
    gtk_entry_set_text(tab_audio->entry_audio_device_id, label);
}

} // namespace YuzuSdlConfig
