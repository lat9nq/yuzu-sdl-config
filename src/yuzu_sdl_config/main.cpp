#include <memory>
#include <basicini/basicini.h>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "hid/hid.h"
#include "yuzu_sdl_config/main_window.h"

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    std::filesystem::path config_path{};
#ifdef __linux__
    const char* xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    const char* home = std::getenv("HOME");

    if (xdg_config_home == nullptr) {
        config_path = home;
        config_path /= ".config/yuzu/sdl2-config.ini";
    } else {
        config_path = xdg_config_home;
        config_path /= "yuzu/sdl2-config.ini";
    }
#else // Generic
    config_path = "sdl2-config.ini";
#endif

    std::unique_ptr<Hid::Hid> hid = std::make_unique<Hid::Hid>();
    std::unique_ptr<BasicIni> ini = std::make_unique<BasicIni>(config_path);
    std::unique_ptr<Settings::Values> values = std::make_unique<Settings::Values>();

    std::unique_ptr<YuzuSdlConfig::MainWindow> main_window =
        std::make_unique<YuzuSdlConfig::MainWindow>(std::move(ini), std::move(values),
                                                    std::move(hid));

    gtk_widget_show(GTK_WIDGET(main_window->window_main));

    gtk_main();
    return 0;
}
