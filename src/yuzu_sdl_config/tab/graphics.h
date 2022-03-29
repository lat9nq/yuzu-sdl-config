#pragma once

#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabGraphics : public Tab {
public:
    explicit TabGraphics(Settings::Values& settings_);
    ~TabGraphics();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    GtkBox* box_graphics;
    GtkLabel* label_shader_backend;
    GtkLabel* label_vulkan_device;
    GtkComboBoxText* combo_box_text_renderer_backend;
    GtkComboBoxText* combo_box_text_shader_backend;
    GtkBox* box_vulkan_device;
    GtkComboBoxText* combo_box_text_vulkan_device;
    GtkEntry* entry_vulkan_device;
    GtkCheckButton* check_button_use_disk_shader_cache;
    GtkCheckButton* check_button_use_asynchronous_gpu_emulation;
    GtkCheckButton* check_button_accelerate_astc;
    GtkComboBoxText* combo_box_text_anti_aliasing;
    GtkComboBoxText* combo_box_text_scaling_filter;
    GtkComboBoxText* combo_box_text_resolution_setup;
    GtkComboBoxText* combo_box_text_aspect_ratio;
    GtkComboBoxText* combo_box_text_fullscreen_mode;
    GtkComboBoxText* combo_box_text_nvdec_emulation;
    GtkColorButton* color_button_bg;

private:
    void BuildUi() override;

    Settings::Values& settings;
};

extern "C" G_MODULE_EXPORT void on_combo_box_text_renderer_backend_changed(GtkComboBox* self,
                                                                           gpointer user_data);
} // namespace YuzuSdlConfig
