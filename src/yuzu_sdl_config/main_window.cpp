#include <cassert>
#include <cstring>
#include <memory>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/main_window.glade.h"
#include "yuzu_sdl_config/main_window.h"

namespace YuzuSdlConfig {
MainWindow::MainWindow() {
    BuildUi();
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

    g_object_ref(window_main);
    g_object_unref(builder);

    page_general = std::make_unique<General>();

    gtk_notebook_append_page(notebook_view, GTK_WIDGET(page_general->grid_general),
                             gtk_label_new("General"));
}

void on_window_main_destroy(GtkWidget* caller, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(caller == GTK_WIDGET(window->window_main));

    gtk_main_quit();
}

void on_file_chooser_button_ini_path_selection_changed(GtkWidget* caller, gpointer user_data) {
    MainWindow* window = static_cast<MainWindow*>(user_data);
    assert(caller == GTK_WIDGET(window->file_chooser_button_ini_path));

    gtk_entry_set_text(window->entry_ini_path, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(
                                                   window->file_chooser_button_ini_path)));
}

void Start(int* argc, char*** argv) {
    gtk_init(argc, argv);

    std::unique_ptr<MainWindow> main_window = std::make_unique<MainWindow>();
    gtk_widget_show(GTK_WIDGET(main_window->window_main));

    gtk_main();
}
} // namespace YuzuSdlConfig
