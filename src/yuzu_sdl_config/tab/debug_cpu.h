#pragma once

#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/tab.h"

namespace Settings {
struct Values;
}

namespace YuzuSdlConfig {
class TabDebugCpu : public Tab {
public:
    explicit TabDebugCpu(Settings::Values& settings_);
    ~TabDebugCpu();

    void UpdateUi() override;
    void ApplyUiConfiguration() override;
    GtkWidget* GetParent() const override;

    GtkBox* box_debug_cpu;
    GtkCheckButton* check_button_cpuopt_page_tables;
    GtkCheckButton* check_button_cpuopt_block_linking;
    GtkCheckButton* check_button_cpuopt_return_stack_buffer;
    GtkCheckButton* check_button_cpuopt_fast_dispatcher;
    GtkCheckButton* check_button_cpuopt_context_elimination;
    GtkCheckButton* check_button_cpuopt_const_prop;
    GtkCheckButton* check_button_cpuopt_misc_ir;
    GtkCheckButton* check_button_cpuopt_reduce_misalign_checks;
    GtkCheckButton* check_button_cpuopt_fastmem;
    GtkCheckButton* check_button_cpuopt_fastmem_exclusives;
    GtkCheckButton* check_button_cpuopt_recompile_exclusives;

private:
    void BuildUi() override;
    Settings::Values& settings;
};
} // namespace YuzuSdlConfig
