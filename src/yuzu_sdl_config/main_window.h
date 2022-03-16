#pragma once

#include <memory>
#include <vector>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab_general.h"

namespace YuzuSdlConfig {
class MainWindow {
public:
    explicit MainWindow(std::unique_ptr<BasicIni> ini_);
    ~MainWindow();

    const std::vector<GtkWidget*>& GetTabList(std::size_t index) const;

    GtkWindow* window_main;
    GtkNotebook* notebook_view;
    GtkEntry* entry_ini_path;
    GtkFileChooserButton* file_chooser_button_ini_path;
    GtkListBox* list_box_view_select;

    std::unique_ptr<TabGeneral> tab_general;
    std::unique_ptr<BasicIni> ini;

private:
    void BuildUi();
    void UpdateUi();
    void PopulateCategories();

    std::vector<std::vector<GtkWidget*>> tab_list;
};

extern "C" G_MODULE_EXPORT void on_window_main_destroy(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_file_chooser_button_ini_path_selection_changed(
    GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_list_box_view_select_row_selected(GtkWidget* self,
                                                                     GtkListBoxRow* row,
                                                                     gpointer user_data);

void Start(int* argc, char*** argv, std::unique_ptr<BasicIni> ini_);
} // namespace YuzuSdlConfig
