#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/web_service.glade.h"
#include "yuzu_sdl_config/tab/web_service.h"

namespace YuzuSdlConfig {
TabWebService::TabWebService(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabWebService::~TabWebService() {
    g_object_unref(box_web_service);
}

void TabWebService::UpdateUi() {
    gtk_entry_set_text(entry_yuzu_username, settings.yuzu_username.GetValue().c_str());
    gtk_entry_set_text(entry_yuzu_token, settings.yuzu_token.GetValue().c_str());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_enable_telemetry),
                                 settings.enable_telemetry.GetValue());
}

void TabWebService::ApplyUiConfiguration() {
    settings.yuzu_username = gtk_entry_get_text(entry_yuzu_username);
    settings.yuzu_token = gtk_entry_get_text(entry_yuzu_token);
    settings.enable_telemetry =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_enable_telemetry));
}

GtkWidget* TabWebService::GetParent() const {
    return GTK_WIDGET(box_web_service);
}

void TabWebService::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(web_service_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_web_service = GTK_BOX(gtk_builder_get_object(builder, "box_web_service"));
    entry_yuzu_username = GTK_ENTRY(gtk_builder_get_object(builder, "entry_yuzu_username"));
    entry_yuzu_token = GTK_ENTRY(gtk_builder_get_object(builder, "entry_yuzu_token"));
    button_verify_token = GTK_BUTTON(gtk_builder_get_object(builder, "button_verify_token"));
    check_button_enable_telemetry =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_enable_telemetry"));

    g_object_ref(box_web_service);
    g_object_unref(builder);
}

} // namespace YuzuSdlConfig
