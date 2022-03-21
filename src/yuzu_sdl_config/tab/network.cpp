#ifdef __linux__
#include <dirent.h>
#include <sys/types.h>
#endif

#include <cassert>
#include <cstring>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/network.glade.h"
#include "yuzu_sdl_config/tab/network.h"

namespace YuzuSdlConfig {
TabNetwork::TabNetwork(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabNetwork::~TabNetwork() {
    g_object_unref(menu_network_interface);
    g_object_unref(box_network);
}

void TabNetwork::UpdateUi() {
    gtk_entry_set_text(entry_network_interface, settings.network_interface.GetValue().c_str());
}

void TabNetwork::ApplyUiConfiguration() {
    settings.network_interface = gtk_entry_get_text(entry_network_interface);
}

GtkWidget* TabNetwork::GetParent() const {
    return GTK_WIDGET(box_network);
}

void TabNetwork::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(network_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_network = GTK_BOX(gtk_builder_get_object(builder, "box_network"));
    menu_button_network_interface =
        GTK_MENU_BUTTON(gtk_builder_get_object(builder, "menu_button_network_interface"));
    entry_network_interface = GTK_ENTRY(gtk_builder_get_object(builder, "entry_network_interface"));
    menu_network_interface = GTK_MENU(gtk_builder_get_object(builder, "menu_network_interface"));

    g_object_ref(menu_network_interface);
    g_object_ref(box_network);
    g_object_unref(builder);

    gtk_widget_set_halign(GTK_WIDGET(menu_network_interface), GTK_ALIGN_END);

    interfaces.push_back("None");
    // Find system network interfaces
#ifdef __linux__
    DIR* net = opendir("/sys/class/net");
    if (net != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(net)) != nullptr) {
            if (std::strncmp(entry->d_name, ".", 256) == 0 ||
                std::strncmp(entry->d_name, "..", 256) == 0 ||
                std::strncmp(entry->d_name, "lo", 256) == 0) {
                continue;
            }
            interfaces.push_back(entry->d_name);
        }

        closedir(net);
    }
#endif
    // Populate interface menu with found interfaces
    for (const std::string& interface : interfaces) {
        GtkWidget* item = gtk_menu_item_new_with_label(interface.c_str());
        gtk_widget_show(item);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_network_interface), item);

        g_signal_connect(G_OBJECT(item), "activate",
                         G_CALLBACK(on_menu_network_interface_item_activate), this);
    }
}

void on_menu_network_interface_item_activate(GtkMenuItem* item, gpointer user_data) {
    TabNetwork* tab_network = static_cast<TabNetwork*>(user_data);

    const char* label = gtk_menu_item_get_label(item);
    gtk_entry_set_text(tab_network->entry_network_interface, label);
}
} // namespace YuzuSdlConfig
