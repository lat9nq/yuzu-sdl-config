#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/web_service.glade.h"
#include "yuzu_sdl_config/tab/web_service.h"

namespace YuzuSdlConfig {
TabWebService::TabWebService(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabWebService::~TabWebService() = default;

void TabWebService::UpdateUi() {}

GtkWidget* TabWebService::GetParent() const {
    return GTK_WIDGET(box_web_service);
}

void TabWebService::BuildUi() {}

} // namespace YuzuSdlConfig
