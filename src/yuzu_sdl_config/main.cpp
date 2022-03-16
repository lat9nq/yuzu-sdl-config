#include <memory>
#include <basicini/basicini.h>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/main_window.h"

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    std::unique_ptr<BasicIni> ini = std::make_unique<BasicIni>("test.ini");
    std::unique_ptr<Settings::Values> values = std::make_unique<Settings::Values>();

    std::unique_ptr<YuzuSdlConfig::MainWindow> main_window =
        std::make_unique<YuzuSdlConfig::MainWindow>(std::move(ini), std::move(values));

    gtk_widget_show(GTK_WIDGET(main_window->window_main));

    gtk_main();
    return 0;
}
