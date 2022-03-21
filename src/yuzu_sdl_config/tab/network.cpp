#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/network.glade.h"
#include "yuzu_sdl_config/tab/network.h"

namespace YuzuSdlConfig {
TabNetwork::TabNetwork(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}
TabNetwork::~TabNetwork() {}

void TabNetwork::UpdateUi() {}
void TabNetwork::ApplyUiConfiguration() {}
GtkWidget* TabNetwork::GetParent() const {
    return GTK_WIDGET(box_network);
}

void TabNetwork::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(network_glade, strlen(network_glade));
    gtk_builder_connect_signals(builder, this);

    box_network = GTK_BOX(gtk_builder_get_object(builder, "box_network"));
    combo_box_text_network_interface =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_network_interface"));

    g_object_ref(box_network);
    g_object_unref(builder);
}
} // namespace YuzuSdlConfig
