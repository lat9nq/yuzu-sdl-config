#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <common/settings.h>
#include <fcntl.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/web_service.glade.h"
#include "yuzu_sdl_config/tab/web_service.h"

#if defined(__linux__)
#include <unistd.h>
#endif

namespace YuzuSdlConfig {
TabWebService::TabWebService(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
    ReadTelemetryId();
}

TabWebService::~TabWebService() {
    g_object_unref(box_web_service);
}

void TabWebService::UpdateUi() {
    gtk_entry_set_text(entry_yuzu_username, settings.yuzu_username.GetValue().c_str());
    gtk_entry_set_text(entry_yuzu_token, settings.yuzu_token.GetValue().c_str());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_enable_telemetry),
                                 settings.enable_telemetry.GetValue());
    UpdateTelemetryId();
}

void TabWebService::UpdateTelemetryId() {
    if (telemetry_id == 0) {
        gtk_label_set_text(label_telemetry_id, "No telemetry ID");
    } else {
        char id[30];
        std::sprintf(id, "0x%016lX", telemetry_id);
        gtk_label_set_text(label_telemetry_id, id);
    }
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
    button_clear_telemetry_id =
        GTK_BUTTON(gtk_builder_get_object(builder, "button_clear_telemetry_id"));
    label_telemetry_id = GTK_LABEL(gtk_builder_get_object(builder, "label_telemetry_id"));

    g_object_ref(box_web_service);
    g_object_unref(builder);
}

void TabWebService::ReadTelemetryId() {
    telemetry_id = 0;
#if defined(__linux__)
    const char* xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    const char* home = std::getenv("HOME");

    if (xdg_config_home == nullptr) {
        telemetry_id_path = home;
        telemetry_id_path /= ".config/yuzu/telemetry_id";
    } else {
        telemetry_id_path = xdg_config_home;
        telemetry_id_path /= "yuzu/telemetry_id";
    }

    int fd = open(telemetry_id_path.c_str(), O_RDONLY);
    if (fd == -1) {
        return;
    }

    u64 id;
    const ssize_t bytes = read(fd, &id, sizeof(id));
    close(fd);
    if (bytes == static_cast<ssize_t>(sizeof(id))) {
        telemetry_id = id;
    }
#endif
}

void TabWebService::ClearTelemetryId() {
    telemetry_id = 0;
#if defined(__linux__)
    const int result = unlink(telemetry_id_path.c_str());
    if (result == -1) {
        std::fprintf(stderr, "error: could not delete %s\n", telemetry_id_path.c_str());
    }
#endif

    UpdateTelemetryId();
}

void on_button_clear_telemetry_id_clicked(GtkButton* self, gpointer user_data) {
    TabWebService* tab_web_service = static_cast<TabWebService*>(user_data);
    assert(tab_web_service->button_clear_telemetry_id == self);

    tab_web_service->ClearTelemetryId();
}
} // namespace YuzuSdlConfig
