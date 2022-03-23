#include <cassert>
#include <common/settings.h>
#include <gtk/gtk.h>
#include "yuzu_sdl_config/tab/filesystem.glade.h"
#include "yuzu_sdl_config/tab/filesystem.h"

namespace YuzuSdlConfig {
TabFilesystem::TabFilesystem(Settings::Values& settings_) : settings{settings_} {
    BuildUi();
}

TabFilesystem::~TabFilesystem() = default;

void TabFilesystem::UpdateUi() {
    const bool gamecard_inserted = settings.gamecard_inserted.GetValue();
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_gamecard_inserted),
                                 gamecard_inserted);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_gamecard_current_game),
                                 settings.gamecard_current_game.GetValue());
    gtk_widget_set_sensitive(GTK_WIDGET(check_button_gamecard_current_game), gamecard_inserted);
    gtk_widget_set_sensitive(GTK_WIDGET(entry_gamecard_path), gamecard_inserted);
    gtk_widget_set_sensitive(GTK_WIDGET(button_gamecard_path), gamecard_inserted);
    gtk_entry_set_text(entry_gamecard_path, settings.gamecard_path.GetValue().c_str());

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_dump_nso),
                                 settings.dump_nso.GetValue());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_dump_exefs),
                                 settings.dump_exefs.GetValue());
}

void TabFilesystem::ApplyUiConfiguration() {
    const bool gamecard_inserted =
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_gamecard_inserted));
    settings.gamecard_inserted = gamecard_inserted;
    if (gamecard_inserted) {
        settings.gamecard_current_game =
            gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_gamecard_current_game));
        const char* gamecard_path = gtk_entry_get_text(entry_gamecard_path);
        settings.gamecard_path = gamecard_path;
    }

    settings.dump_nso = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_dump_nso));
    settings.dump_exefs = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button_dump_exefs));
}

GtkWidget* TabFilesystem::GetParent() const {
    return GTK_WIDGET(box_filesystem);
}

void TabFilesystem::BuildUi() {
    GtkBuilder* builder = gtk_builder_new_from_string(filesystem_glade, -1);
    gtk_builder_connect_signals(builder, this);

    box_filesystem = GTK_BOX(gtk_builder_get_object(builder, "box_filesystem"));
    check_button_gamecard_inserted =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_gamecard_inserted"));
    check_button_gamecard_current_game =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_gamecard_current_game"));
    entry_gamecard_path = GTK_ENTRY(gtk_builder_get_object(builder, "entry_gamecard_path"));
    button_gamecard_path = GTK_BUTTON(gtk_builder_get_object(builder, "button_gamecard_path"));
    check_button_dump_nso =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_dump_nso"));
    check_button_dump_exefs =
        GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_button_dump_exefs"));

    g_object_ref(box_filesystem);
    g_object_unref(builder);
}

void on_button_gamecard_path_clicked(GtkButton* self, gpointer user_data) {
    TabFilesystem* tab_filesystem = static_cast<TabFilesystem*>(user_data);
    assert(tab_filesystem->button_gamecard_path == self);

    const GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

    GtkFileChooserNative* file_chooser =
        gtk_file_chooser_native_new("Select Gamecard Path", nullptr, action, "_Open", "_Cancel");

    const int result = gtk_native_dialog_run(GTK_NATIVE_DIALOG(file_chooser));
    if (result == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
        gtk_entry_set_text(tab_filesystem->entry_gamecard_path, filename);
        g_free(filename);
    }

    g_object_unref(file_chooser);
}

void on_check_button_gamecard_inserted_toggled(GtkToggleButton* self, gpointer user_data) {
    TabFilesystem* tab_filesystem = static_cast<TabFilesystem*>(user_data);
    assert(GTK_TOGGLE_BUTTON(tab_filesystem->check_button_gamecard_inserted) == self);

    const bool sensitive = gtk_toggle_button_get_active(self);
    gtk_widget_set_sensitive(GTK_WIDGET(tab_filesystem->check_button_gamecard_current_game),
                             sensitive);
    gtk_widget_set_sensitive(GTK_WIDGET(tab_filesystem->entry_gamecard_path), sensitive);
    gtk_widget_set_sensitive(GTK_WIDGET(tab_filesystem->button_gamecard_path), sensitive);
}
} // namespace YuzuSdlConfig
