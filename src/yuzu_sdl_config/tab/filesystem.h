#pragma once

#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabFilesystem : public Tab {
public:
    explicit TabFilesystem(Settings::Values& settings_);
    ~TabFilesystem();

    GtkBox* box_filesystem;
    GtkCheckButton* check_button_gamecard_inserted;
    GtkCheckButton* check_button_gamecard_current_game;
    GtkEntry* entry_gamecard_path;
    GtkButton* button_gamecard_path;
    GtkCheckButton* check_button_dump_nso;
    GtkCheckButton* check_button_dump_exefs;

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

private:
    void BuildUi() override;

    Settings::Values& settings;
};

extern "C" G_MODULE_EXPORT void on_button_gamecard_path_clicked(GtkButton* self,
                                                                gpointer user_data);
extern "C" G_MODULE_EXPORT void on_check_button_gamecard_inserted_toggled(GtkToggleButton* self,
                                                                          gpointer user_data);
} // namespace YuzuSdlConfig
