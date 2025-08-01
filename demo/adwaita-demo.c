#include "config.h"

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <adwaita.h>

#include "adw-demo-debug-info.h"
#include "adw-demo-preferences-dialog.h"
#include "adw-demo-window.h"

static void
show_inspector (GSimpleAction *action,
                GVariant      *state,
                gpointer       user_data)
{
  gtk_window_set_interactive_debugging (TRUE);
}

static void
show_preferences (GSimpleAction *action,
                  GVariant      *state,
                  gpointer       user_data)
{
  GtkApplication *app = GTK_APPLICATION (user_data);
  GtkWindow *window = gtk_application_get_active_window (app);

  adw_dialog_present (adw_demo_preferences_dialog_new (), GTK_WIDGET (window));
}

static void
show_about (GSimpleAction *action,
            GVariant      *state,
            gpointer       user_data)
{
  const char *developers[] = {
    "Adrien Plazas",
    "Alice Mikhaylenko",
    "Andrei Lișiță",
    "Guido Günther",
    "Jamie Murphy",
    "Julian Sparber",
    "Manuel Genovés",
    "Zander Brown",
    NULL
  };

  const char *designers[] = {
    "GNOME Design Team",
    NULL
 };

  GtkApplication *app = GTK_APPLICATION (user_data);
  GtkWindow *window = gtk_application_get_active_window (app);
  char *debug_info;
  AdwDialog *about;

  debug_info = adw_demo_generate_debug_info ();

  about = adw_about_dialog_new_from_appdata ("/org/gnome/Adwaita1/Demo/org.gnome.Adwaita1.Demo.metainfo.xml", NULL);
  adw_about_dialog_set_version (ADW_ABOUT_DIALOG (about), ADW_VERSION_S);
  adw_about_dialog_set_debug_info (ADW_ABOUT_DIALOG (about), debug_info);
  adw_about_dialog_set_debug_info_filename (ADW_ABOUT_DIALOG (about), "adwaita-1-demo-debug-info.txt");
  adw_about_dialog_set_copyright (ADW_ABOUT_DIALOG (about), "© 2017–2022 Purism SPC\n© 2023-2024 GNOME Foundation Inc.");
  adw_about_dialog_set_developers (ADW_ABOUT_DIALOG (about), developers);
  adw_about_dialog_set_designers (ADW_ABOUT_DIALOG (about), designers);
  adw_about_dialog_set_artists (ADW_ABOUT_DIALOG (about), designers);
  adw_about_dialog_set_translator_credits (ADW_ABOUT_DIALOG (about), _("translator-credits"));

  adw_about_dialog_add_link (ADW_ABOUT_DIALOG (about),
                             _("_Documentation"),
                             "https://gnome.pages.gitlab.gnome.org/libadwaita/doc/main/");
  adw_about_dialog_add_link (ADW_ABOUT_DIALOG (about),
                             _("_Chat"),
                             "https://matrix.to/#/#libadwaita:gnome.org");

  adw_dialog_present (about, GTK_WIDGET (window));

  g_free (debug_info);
}

static void
quit_app (GSimpleAction *action,
          GVariant      *state,
          gpointer       user_data)
{
  GApplication *app = G_APPLICATION (user_data);

  g_application_quit (app);
}

static void
show_window (GtkApplication *app)
{
  gtk_window_present (adw_demo_window_new (app));
}

int
main (int    argc,
      char **argv)
{
  AdwApplication *app;
  int status;
  static GActionEntry app_entries[] = {
    { "inspector", show_inspector, NULL, NULL, NULL },
    { "preferences", show_preferences, NULL, NULL, NULL },
    { "about", show_about, NULL, NULL, NULL },
    { "quit", quit_app, NULL, NULL, NULL },
  };
  const char *preferences_accels[2] = { "<Ctrl>comma", NULL };
  const char *quit_accels[2] = { "<Ctrl>Q", NULL };

  app = adw_application_new ("org.gnome.Adwaita1.Demo", G_APPLICATION_NON_UNIQUE);
  g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   app_entries, G_N_ELEMENTS (app_entries),
                                   app);

  gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.preferences", preferences_accels);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.quit", quit_accels);

  g_signal_connect (app, "activate", G_CALLBACK (show_window), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
