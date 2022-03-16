#pragma once

#include <memory>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/general.h"

namespace YuzuSdlConfig {
class MainWindow {
public:
    explicit MainWindow();
    ~MainWindow();

    GtkWindow* window_main;
    GtkNotebook* notebook_view;
    GtkEntry* entry_ini_path;
    GtkFileChooserButton* file_chooser_button_ini_path;

    std::unique_ptr<General> page_general;

private:
    void BuildUi();
};

extern "C" G_MODULE_EXPORT void on_window_main_destroy(GtkWidget* caller, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_file_chooser_button_ini_path_selection_changed(
    GtkWidget* self, gpointer user_data);

void Start(int* argc, char*** argv);
} // namespace YuzuSdlConfig
