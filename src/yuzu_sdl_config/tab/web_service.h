#pragma once

#include <filesystem>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabWebService : public Tab {
public:
    explicit TabWebService(Settings::Values& settings_);
    ~TabWebService();

    GtkBox* box_web_service;
    GtkEntry* entry_yuzu_token;
    GtkEntry* entry_yuzu_username;
    GtkButton* button_verify_token;
    GtkCheckButton* check_button_enable_telemetry;
    GtkButton* button_clear_telemetry_id;
    GtkLabel* label_telemetry_id;

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    void ClearTelemetryId();

private:
    void BuildUi() override;
    void ReadTelemetryId();
    void UpdateTelemetryId();

    Settings::Values& settings;
    u64 telemetry_id{};
    std::filesystem::path telemetry_id_path{};
};

extern "C" G_MODULE_EXPORT void on_button_clear_telemetry_id_clicked(GtkButton* self,
                                                                     gpointer user_data);
} // namespace YuzuSdlConfig
