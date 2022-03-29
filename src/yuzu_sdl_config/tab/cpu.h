#pragma once

#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabCpu : public Tab {
public:
    explicit TabCpu(Settings::Values& settings_);
    ~TabCpu();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    GtkBox* box_cpu;
    GtkComboBoxText* combo_box_text_cpu_accuracy;
    GtkFrame* frame_unsafe_settings;
    GtkCheckButton* check_button_cpuopt_unsafe_unfuse_fma;
    GtkCheckButton* check_button_cpuopt_unsafe_reduce_fp_error;
    GtkCheckButton* check_button_cpuopt_unsafe_ignore_standard_fpcr;
    GtkCheckButton* check_button_cpuopt_unsafe_inaccurate_nan;
    GtkCheckButton* check_button_cpuopt_unsafe_fastmem_check;
    GtkCheckButton* check_button_cpuopt_unsafe_ignore_global_monitor;

private:
    void BuildUi() override;

    Settings::Values& settings;
};

extern "C" G_MODULE_EXPORT void on_combo_box_text_cpu_accuracy_changed(GtkComboBox* self,
                                                                       gpointer user_data);
} // namespace YuzuSdlConfig
