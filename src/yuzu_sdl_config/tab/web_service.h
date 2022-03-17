#pragma once

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

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

private:
    void BuildUi() override;

    Settings::Values& settings;
};
} // namespace YuzuSdlConfig
