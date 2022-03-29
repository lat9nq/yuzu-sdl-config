#include <cassert>
#include <string>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/graphics.glade.h"
#include "yuzu_sdl_config/tab/graphics.h"

namespace YuzuSdlConfig {
TabGraphics::TabGraphics(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabGraphics::~TabGraphics() {
    g_object_unref(box_graphics);
}

void TabGraphics::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(graphics_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_graphics = GTK_BOX(gtk_builder_get_object(builder, "box_graphics"));
    label_shader_backend = GTK_LABEL(gtk_builder_get_object(builder, "label_shader_backend"));
    label_vulkan_device = GTK_LABEL(gtk_builder_get_object(builder, "label_vulkan_device"));
    combo_box_text_renderer_backend =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_renderer_backend"));
    combo_box_text_shader_backend =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_shader_backend"));
    box_vulkan_device = GTK_BOX(gtk_builder_get_object(builder, "box_vulkan_device"));
    combo_box_text_vulkan_device =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_vulkan_device"));
    entry_vulkan_device = GTK_ENTRY(gtk_builder_get_object(builder, "entry_vulkan_device"));
    check_button_use_disk_shader_cache =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_disk_shader_cache"));
    check_button_use_asynchronous_gpu_emulation = GTK_CHECK_BUTTON(
        gtk_builder_get_object(builder, "check_button_use_asynchronous_gpu_emulation"));
    check_button_accelerate_astc =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_accelerate_astc"));
    combo_box_text_anti_aliasing =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_anti_aliasing"));
    combo_box_text_scaling_filter =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_scaling_filter"));
    combo_box_text_resolution_setup =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_resolution_setup"));
    combo_box_text_aspect_ratio =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_aspect_ratio"));
    combo_box_text_fullscreen_mode =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_fullscreen_mode"));
    combo_box_text_nvdec_emulation =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_nvdec_emulation"));
    color_button_bg = GTK_COLOR_BUTTON(gtk_builder_get_object(builder, "color_button_bg"));

    g_object_ref(box_graphics);
    g_object_unref(builder);
}

void TabGraphics::UpdateUi() {
    const std::string vulkan_device = std::to_string(settings.vulkan_device.GetValue());
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_renderer_backend),
                             static_cast<int>(settings.renderer_backend.GetValue()));
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_shader_backend),
                             static_cast<int>(settings.shader_backend.GetValue()));
    gtk_entry_set_text(entry_vulkan_device, vulkan_device.c_str());

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_disk_shader_cache),
                                 settings.use_disk_shader_cache.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_asynchronous_gpu_emulation),
                                 settings.use_asynchronous_gpu_emulation.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_accelerate_astc),
                                 settings.accelerate_astc.GetValue());
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_anti_aliasing),
                             static_cast<int>(settings.anti_aliasing.GetValue()));
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_scaling_filter),
                             static_cast<int>(settings.scaling_filter.GetValue()));
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_resolution_setup),
                             static_cast<int>(settings.resolution_setup.GetValue()));
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_aspect_ratio),
                             settings.aspect_ratio.GetValue());
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_fullscreen_mode),
                             static_cast<int>(settings.fullscreen_mode.GetValue()));
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_nvdec_emulation),
                             static_cast<int>(settings.nvdec_emulation.GetValue()));
    const GdkRGBA bg_color{settings.bg_red.GetValue() / 255.0, settings.bg_red.GetValue() / 255.0,
                           settings.bg_blue.GetValue() / 255.0, 1.0};
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_button_bg), &bg_color);
}

void TabGraphics::ApplyUiConfiguration() {
    settings.renderer_backend = static_cast<Settings::RendererBackend>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_renderer_backend)));
    settings.shader_backend = static_cast<Settings::ShaderBackend>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_shader_backend)));
    settings.vulkan_device = std::atoi(gtk_entry_get_text(entry_vulkan_device));

    settings.use_disk_shader_cache =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_use_disk_shader_cache));
    settings.use_asynchronous_gpu_emulation = gtk_toggle_button_get_active(
        GTK_TOGGLE_BUTTON(check_button_use_asynchronous_gpu_emulation));
    settings.accelerate_astc =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_accelerate_astc));
    settings.anti_aliasing = static_cast<Settings::AntiAliasing>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_anti_aliasing)));
    settings.scaling_filter = static_cast<Settings::ScalingFilter>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_scaling_filter)));
    settings.resolution_setup = static_cast<Settings::ResolutionSetup>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_resolution_setup)));
    settings.fullscreen_mode = static_cast<Settings::FullscreenMode>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_fullscreen_mode)));
    settings.nvdec_emulation = static_cast<Settings::NvdecEmulation>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_nvdec_emulation)));

    GdkRGBA bg_color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(color_button_bg), &bg_color);
    settings.bg_red = static_cast<u8>(bg_color.red * 255.0);
    settings.bg_green = static_cast<u8>(bg_color.green * 255.0);
    settings.bg_blue = static_cast<u8>(bg_color.blue * 255.0);
}

GtkWidget* TabGraphics::GetParent() const {
    return GTK_WIDGET(box_graphics);
}

void on_combo_box_text_renderer_backend_changed(GtkComboBox* self, gpointer user_data) {
    TabGraphics* tab_graphics = static_cast<TabGraphics*>(user_data);
    assert(tab_graphics->combo_box_text_renderer_backend == GTK_COMBO_BOX_TEXT(self));

    const Settings::RendererBackend backend =
        static_cast<Settings::RendererBackend>(gtk_combo_box_get_active(self));
    const bool show_gl_settings = (backend == Settings::RendererBackend::OpenGL);
    gtk_widget_set_visible(GTK_WIDGET(tab_graphics->label_shader_backend), show_gl_settings);
    gtk_widget_set_visible(GTK_WIDGET(tab_graphics->combo_box_text_shader_backend),
                           show_gl_settings);
    gtk_widget_set_visible(GTK_WIDGET(tab_graphics->label_vulkan_device), !show_gl_settings);
    gtk_widget_set_visible(GTK_WIDGET(tab_graphics->box_vulkan_device), !show_gl_settings);
}
} // namespace YuzuSdlConfig
