#include <cstring>
#include "yuzu_sdl_config/tab_debug.glade.h"
#include "yuzu_sdl_config/tab_debug.h"

namespace YuzuSdlConfig {
TabDebug::TabDebug(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabDebug::~TabDebug() {
    g_object_unref(box_debug);
}

void TabDebug::BuildUi() {
    GtkBuilder* builder =
        gtk_builder_new_from_string(tab_debug_configuration, strlen(tab_debug_configuration));
    gtk_builder_connect_signals(builder, this);

    box_debug = GTK_BOX(gtk_builder_get_object(builder, "box_debug"));

    g_object_ref(box_debug);
    g_object_unref(builder);
}

void TabDebug::UpdateUi() {}

GtkWidget* TabDebug::GetParent() const {
    return GTK_WIDGET(box_debug);
}
} // namespace YuzuSdlConfig
