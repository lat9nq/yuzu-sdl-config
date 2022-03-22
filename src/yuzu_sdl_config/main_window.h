#pragma once

#include <memory>
#include <vector>
#include <common/settings.h>
#include <gtk/gtk.h>

namespace YuzuSdlConfig {
class TabGeneral;
class TabDebug;
class TabDebugCpu;
class TabWebService;
class TabSystem;
class TabNetwork;

class MainWindow {
public:
    explicit MainWindow(std::unique_ptr<BasicIni> ini_,
                        std::unique_ptr<Settings::Values> settings_);
    ~MainWindow();
    void UpdateUi();
    void ReadIni();

    const std::vector<GtkWidget*>& GetTabList(std::size_t index) const;

    GtkWindow* window_main;
    GtkNotebook* notebook_view;
    GtkListBox* list_box_view_select;
    GtkToolButton* tool_button_about;
    GtkToolButton* tool_button_open;
    GtkToolButton* tool_button_save;
    GtkToolButton* tool_button_save_as;
    GtkToolButton* tool_button_revert;
    GtkToolButton* tool_button_reset;

    GtkAboutDialog* about_dialog_main;
    GtkButton* button_about_close;

    std::unique_ptr<TabGeneral> tab_general;
    std::unique_ptr<TabDebug> tab_debug;
    std::unique_ptr<TabDebugCpu> tab_debug_cpu;
    std::unique_ptr<TabWebService> tab_web_service;
    std::unique_ptr<TabSystem> tab_system;
    std::unique_ptr<TabNetwork> tab_network;
    std::unique_ptr<BasicIni> ini;

private:
    void BuildUi();
    void ApplyUiConfiguration();
    void PopulateCategories();

    std::unique_ptr<Settings::Values> settings;
    std::vector<std::vector<GtkWidget*>> tab_list;
};

extern "C" G_MODULE_EXPORT void on_button_about_close_clicked(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_tool_button_about_clicked(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_tool_button_open_clicked(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_tool_button_reset_clicked(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_tool_button_revert_clicked(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_tool_button_save_as_clicked(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_tool_button_save_clicked(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_window_main_destroy(GtkWidget* self, gpointer user_data);
extern "C" G_MODULE_EXPORT void on_list_box_view_select_row_selected(GtkWidget* self,
                                                                     GtkListBoxRow* row,
                                                                     gpointer user_data);
} // namespace YuzuSdlConfig
