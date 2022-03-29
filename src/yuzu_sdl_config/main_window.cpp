#include <cassert>
#include <memory>
#include <vector>
#include <basicini/basicini.h>
#include <basicini/basicini_reader.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/config.h"
#include "yuzu_sdl_config/main_window.glade.h"
#include "yuzu_sdl_config/main_window.h"
#include "yuzu_sdl_config/tab/cpu.h"
#include "yuzu_sdl_config/tab/debug.h"
#include "yuzu_sdl_config/tab/debug_cpu.h"
#include "yuzu_sdl_config/tab/filesystem.h"
#include "yuzu_sdl_config/tab/general.h"
#include "yuzu_sdl_config/tab/graphics.h"
#include "yuzu_sdl_config/tab/graphics_advanced.h"
#include "yuzu_sdl_config/tab/network.h"
#include "yuzu_sdl_config/tab/system.h"
#include "yuzu_sdl_config/tab/web_service.h"

namespace YuzuSdlConfig {

MainWindow::MainWindow(std::unique_ptr<BasicIni> ini_, std::unique_ptr<Settings::Values> settings_)
    : ini{std::move(ini_)}, settings{std::move(settings_)} {
    BuildUi();
    ReadIni();
    UpdateUi();
}
MainWindow::~MainWindow() {
    g_object_ref(about_dialog_main);
    g_object_unref(window_main);
}

void MainWindow::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(main_window_glade, -1);
    gtk_builder_connect_signals(builder, this);

    window_main = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    notebook_view = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook_view"));
    list_box_view_select = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_box_view_select"));
    about_dialog_main = GTK_ABOUT_DIALOG(gtk_builder_get_object(builder, "about_dialog_main"));
    button_about_close = GTK_BUTTON(gtk_builder_get_object(builder, "button_about_close"));
    tool_button_about = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "tool_button_about"));
    tool_button_open = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "tool_button_open"));
    tool_button_save = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "tool_button_save"));
    tool_button_save_as = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "tool_button_save_as"));
    tool_button_reset = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "tool_button_reset"));
    tool_button_revert = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "tool_button_revert"));

    gtk_window_set_transient_for(GTK_WINDOW(about_dialog_main), window_main);

    g_object_ref(window_main);
    g_object_ref(about_dialog_main);
    g_object_unref(builder);

    tab_cpu = std::make_unique<TabCpu>(*settings);
    tab_debug = std::make_unique<TabDebug>(*settings);
    tab_debug_cpu = std::make_unique<TabDebugCpu>(*settings);
    tab_filesystem = std::make_unique<TabFilesystem>(*settings);
    tab_general = std::make_unique<TabGeneral>(*settings);
    tab_graphics = std::make_unique<TabGraphics>(*settings);
    tab_graphics_advanced = std::make_unique<TabGraphicsAdvanced>(*settings);
    tab_network = std::make_unique<TabNetwork>(*settings);
    tab_system = std::make_unique<TabSystem>(*settings);
    tab_web_service = std::make_unique<TabWebService>(*settings);

    PopulateCategories();
}

void MainWindow::ReadIni() {
    BasicIniReader reader{*ini};
    reader.ReadFile();
    if (!reader.IsValid()) {
        ini->Clear();
    }
}

void MainWindow::UpdateUi() {
    gtk_window_set_title(window_main, ini->GetPath().string().c_str());
    LoadConfig(*ini, *settings);

    tab_cpu->UpdateUi();
    tab_debug->UpdateUi();
    tab_debug_cpu->UpdateUi();
    tab_filesystem->UpdateUi();
    tab_general->UpdateUi();
    tab_graphics->UpdateUi();
    tab_graphics_advanced->UpdateUi();
    tab_network->UpdateUi();
    tab_system->UpdateUi();
    tab_web_service->UpdateUi();
}

void MainWindow::ApplyUiConfiguration() {
    tab_cpu->ApplyUiConfiguration();
    tab_debug->ApplyUiConfiguration();
    tab_debug_cpu->ApplyUiConfiguration();
    tab_filesystem->ApplyUiConfiguration();
    tab_general->ApplyUiConfiguration();
    tab_graphics->ApplyUiConfiguration();
    tab_graphics_advanced->ApplyUiConfiguration();
    tab_network->ApplyUiConfiguration();
    tab_system->ApplyUiConfiguration();
    tab_web_service->ApplyUiConfiguration();
}

void MainWindow::PopulateCategories() {
    const std::array<std::pair<const char*, std::vector<GtkWidget*>>, 6> categories{
        {{"General",
          {tab_general->GetParent(), tab_web_service->GetParent(), tab_debug->GetParent(),
           tab_debug_cpu->GetParent()}},
         {"System",
          {tab_system->GetParent(), tab_network->GetParent(), tab_filesystem->GetParent()}},
         {"CPU", {tab_cpu->GetParent()}},
         {"Graphics", {tab_graphics->GetParent(), tab_graphics_advanced->GetParent()}},
         {"Audio", {}},
         {"Controls", {}}},
    };

    tab_list.clear();
    for (const auto& category : categories) {
        auto label = gtk_label_new(category.first);
        gtk_widget_set_halign(GTK_WIDGET(label), GTK_ALIGN_START);
        gtk_widget_show(GTK_WIDGET(label));
        gtk_container_add(GTK_CONTAINER(list_box_view_select), GTK_WIDGET(label));

        tab_list.push_back(category.second);
    }

    gtk_list_box_select_row(list_box_view_select,
                            gtk_list_box_get_row_at_index(list_box_view_select, 0));
}

const std::vector<GtkWidget*>& MainWindow::GetTabList(std::size_t index) const {
    return tab_list[index];
}

void on_button_about_close_clicked(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->button_about_close));

    gtk_widget_hide(GTK_WIDGET(window->about_dialog_main));
}

void on_tool_button_about_clicked(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->tool_button_about));

    gtk_widget_show(GTK_WIDGET(window->about_dialog_main));
}

void on_tool_button_open_clicked(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->tool_button_open));

    // ini_filter does not need to be manually unref'd since native takes ownership of it
    GtkFileFilter* ini_filter = gtk_file_filter_new();
    gtk_file_filter_add_mime_type(ini_filter, "text/ini");
    gtk_file_filter_add_pattern(ini_filter, "*.ini");

    GtkFileChooserNative* native = gtk_file_chooser_native_new(
        "Open", window->window_main, GTK_FILE_CHOOSER_ACTION_OPEN, "_Open", "_Cancel");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(native), ini_filter);

    int result = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
    if (result == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(native));

        window->ini->SetPath(filename);
        window->ReadIni();
        window->UpdateUi();

        g_free(filename);
    }
    g_object_unref(native);
}

void on_tool_button_reset_clicked(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->tool_button_reset));

    window->ini->Clear();
    window->UpdateUi();
}

void on_tool_button_revert_clicked(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->tool_button_revert));

    window->ReadIni();
    window->UpdateUi();
}

void on_tool_button_save_as_clicked(GtkWidget* self, gpointer user_data) {}
void on_tool_button_save_clicked(GtkWidget* self, gpointer user_data) {}

void on_window_main_destroy(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->window_main));

    gtk_main_quit();
}

void on_list_box_view_select_row_selected(GtkWidget* self, GtkListBoxRow* row, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->list_box_view_select));

    const int page_count = gtk_notebook_get_n_pages(window->notebook_view);
    for (int i = 0; i < page_count; i++) {
        gtk_notebook_remove_page(window->notebook_view, 0);
    }

    const int row_index = gtk_list_box_row_get_index(row);
    const std::vector<GtkWidget*>& tabs = window->GetTabList(row_index);
    for (const auto& widget : tabs) {
        gtk_notebook_append_page(window->notebook_view, widget,
                                 gtk_label_new(gtk_widget_get_name(widget)));
    }
}
} // namespace YuzuSdlConfig
