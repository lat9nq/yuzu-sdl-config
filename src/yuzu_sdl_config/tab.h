#pragma once

#include <gtk/gtk.h>

namespace YuzuSdlConfig {
class Tab {
public:
    Tab(){};
    virtual ~Tab(){};

    virtual void UpdateUi() = 0;
    virtual GtkWidget* GetParent() = 0;
};
} // namespace YuzuSdlConfig
