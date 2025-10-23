#include <gtk/gtk.h>

static void activate(GtkApplication *app){
    GtkWidget *win;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "Leydata");
    gtk_window_set_default_size(GTK_WINDOW(win), 1024, 720);
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);

    gtk_window_present(GTK_WINDOW(win));
}

int main(int argc, char **argv){
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.abhishek01s.leydata", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return stat;
}