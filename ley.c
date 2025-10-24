#include <gtk/gtk.h>

static const char *css_data =
    ".rbox{"
    "background-color: #00babe;"
    "}"
    ".button{"
    //"background-image: none;"
    "background-color: #0b00b5;"
    "min-width: 100px;"
    "}";

static void loadCss(void){
    GtkCssProvider *provider;
    GdkDisplay *display;

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css_data, -1);

    display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

static void activate(GtkApplication *app){
    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *rbox;
    GtkWidget *scr;
    GtkWidget *pic;
    GtkWidget *btn1, *btn2, *btn3;

    loadCss();

    win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Leydata");
    gtk_window_set_default_size(GTK_WINDOW(win), 1024, 720);
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_window_set_child(GTK_WINDOW(win), box);

    scr = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scr, 448, 315);
    gtk_widget_set_hexpand(scr, FALSE);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scr), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

    rbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(rbox, TRUE);
    gtk_widget_set_vexpand(rbox, TRUE);
    gtk_box_set_spacing(GTK_BOX(rbox), 10);
    gtk_widget_add_css_class(rbox, "rbox");

    btn1 = gtk_button_new_with_label("Create");
    btn2 = gtk_button_new_with_label("Read");
    btn3 = gtk_button_new_with_label("Update");
    gtk_widget_add_css_class(btn1, "button");
    gtk_widget_add_css_class(btn2, "button");
    gtk_widget_add_css_class(btn3, "button");

    gtk_widget_set_halign(btn1, GTK_ALIGN_CENTER);

    //gtk_widget_set_halign(rbox, GTK_ALIGN_CENTER);
    //gtk_widget_set_valign(rbox, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(rbox), btn1);
    gtk_box_append(GTK_BOX(rbox), btn2);
    gtk_box_append(GTK_BOX(rbox), btn3);

    pic = gtk_picture_new_for_filename("./mountain-8370051_1280.jpg");
    //gtk_picture_set_can_shrink(GTK_PICTURE(pic), TRUE);
    gtk_picture_set_content_fit(GTK_PICTURE(pic), GTK_CONTENT_FIT_COVER);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), pic);

    gtk_box_append(GTK_BOX(box), scr);
    gtk_box_append(GTK_BOX(box), rbox);

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