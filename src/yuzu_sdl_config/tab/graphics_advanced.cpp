#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/graphics_advanced.glade.h"
#include "yuzu_sdl_config/tab/graphics_advanced.h"

namespace YuzuSdlConfig {
TabGraphicsAdvanced::TabGraphicsAdvanced(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabGraphicsAdvanced::~TabGraphicsAdvanced() {
    g_object_unref(box_graphics_advanced);
}

void TabGraphicsAdvanced::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(graphics_advanced_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_graphics_advanced = GTK_BOX(gtk_builder_get_object(builder, "box_graphics_advanced"));
    check_button_use_vsync =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_vsync"));
    check_button_use_asynchronous_shaders =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_asynchronous_shaders"));
    check_button_use_fast_gpu_time =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_use_fast_gpu_time"));
    combo_box_text_gpu_accuracy =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_gpu_accuracy"));
    combo_box_text_max_anisotropy =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_text_max_anisotropy"));

    g_object_ref(box_graphics_advanced);
    g_object_unref(builder);
}

void TabGraphicsAdvanced::UpdateUi() {
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_gpu_accuracy),
                             static_cast<int>(settings.gpu_accuracy.GetValue()));
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_vsync),
                                 settings.use_vsync.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_asynchronous_shaders),
                                 settings.use_asynchronous_shaders.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_use_fast_gpu_time),
                                 settings.use_fast_gpu_time.GetValue());
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box_text_max_anisotropy),
                             settings.max_anisotropy.GetValue());
}

void TabGraphicsAdvanced::ApplyUiConfiguration() {
    settings.gpu_accuracy = static_cast<Settings::GPUAccuracy>(
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_gpu_accuracy)));
    settings.use_vsync = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_use_vsync));
    settings.use_asynchronous_shaders =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_use_asynchronous_shaders));
    settings.use_fast_gpu_time =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_use_fast_gpu_time));
    settings.max_anisotropy =
        gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box_text_max_anisotropy));
}

GtkWidget* TabGraphicsAdvanced::GetParent() const {
    return GTK_WIDGET(box_graphics_advanced);
}
} // namespace YuzuSdlConfig
