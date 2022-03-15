#pragma once

#include <gtk/gtk.h>

namespace YuzuSdlConfig {
class MainWindow {
public:
    explicit MainWindow();
    ~MainWindow();

    GtkWindow* window_main;

private:
    void BuildUi();
};

extern "C" G_MODULE_EXPORT void on_window_main_destroy(GtkWidget* caller, gpointer user_data);

void Start(int* argc, char*** argv);
} // namespace YuzuSdlConfig
