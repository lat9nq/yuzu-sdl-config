#include <cassert>
#include <cstring>
#include <memory>
#include <vector>
#include <basicini/basicini.h>
#include <basicini/basicini_reader.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/main_window.glade.h"
#include "yuzu_sdl_config/main_window.h"
#include "yuzu_sdl_config/tab_general.h"

namespace YuzuSdlConfig {

MainWindow::MainWindow(std::unique_ptr<BasicIni> ini_) : ini{std::move(ini_)} {
    BasicIniReader reader(*ini);
    reader.ReadFile();
    if (!reader.IsValid()) {
        ini->Clear();
    }

    BuildUi();
    UpdateUi();
}
MainWindow::~MainWindow() = default;

void MainWindow::BuildUi() {
    GtkBuilder* builder =
        gtk_builder_new_from_string(main_window_configuration, strlen(main_window_configuration));
    gtk_builder_connect_signals(builder, this);

    window_main = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    notebook_view = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook_view"));
    entry_ini_path = GTK_ENTRY(gtk_builder_get_object(builder, "entry_ini_path"));
    file_chooser_button_ini_path =
        GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file_chooser_button_ini_path"));
    list_box_view_select = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_box_view_select"));

    g_object_ref(window_main);
    g_object_unref(builder);

    tab_general = std::make_unique<TabGeneral>(*ini);

    PopulateCategories();
}

void MainWindow::UpdateUi() {
    tab_general->UpdateUi();

    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser_button_ini_path),
                                  ini->GetPath().string().c_str());
}

void MainWindow::PopulateCategories() {
    const std::array<std::pair<const char*, std::vector<GtkWidget*>>, 6> categories{
        {{"General", {tab_general->GetParent()}},
         {"System", {}},
         {"CPU", {}},
         {"Graphics", {}},
         {"Audio", {}},
         {"Controls", {}}},
    };

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

void on_window_main_destroy(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->window_main));

    gtk_main_quit();
}

void on_file_chooser_button_ini_path_selection_changed(GtkWidget* self, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(self == GTK_WIDGET(window->file_chooser_button_ini_path));

    gtk_entry_set_text(window->entry_ini_path, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(
                                                   window->file_chooser_button_ini_path)));
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

void Start(int* argc, char*** argv, std::unique_ptr<BasicIni> ini_) {
    gtk_init(argc, argv);

    std::unique_ptr<MainWindow> main_window = std::make_unique<MainWindow>(std::move(ini_));
    gtk_widget_show(GTK_WIDGET(main_window->window_main));

    gtk_main();
}
} // namespace YuzuSdlConfig
