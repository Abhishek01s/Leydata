#include "leydata.h"

#define APPLICATION_NAME "Leydata"

static void closeWindow(GtkWidget *widget, GtkWindow *win){
    gtk_window_close(win);
}

static void loadCss(void){
    GtkCssProvider *provider;
    GdkDisplay *display;

    const char *css_data =
    ".sideBox{"
    "background-color: #FAF8F1;"
    "}"
    ".button{"
    "background-color: #FAEAB1;"
    "color: #334443;"
    "font-size: 24px;"
    "min-width: 225px;"
    "}"
    ".nameLabel{"
    "margin-top: 64px;"
    "color: #334443;"
    "font-size: 32px;"
    "}";

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, css_data);

    display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

static void activate(GtkApplication *app){
    GtkWidget *win;
    GtkWidget *mainBox, *sideBox, *btnBox;
    GtkWidget *scrolledWin;
    GtkWidget *pic;
    GtkWidget *nameLabel;
    GtkWidget *btnCreate, *btnRead, *btnUpdate, *btnExit;

    loadCss();

    // Create and configure a Top Window
    win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), APPLICATION_NAME);
    gtk_window_set_default_size(GTK_WINDOW(win), 1024, 720);
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);

    // Create the outer GtkBox
    mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    // Create and configure a GtkScrolledWindow
    scrolledWin = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolledWin, 448, 315);
    gtk_widget_set_hexpand(scrolledWin, FALSE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWin), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

    // Create and configure a GtkImage to use in the menu
    pic = gtk_picture_new_for_filename("./mountain-8370051_1280.jpg");
    gtk_picture_set_content_fit(GTK_PICTURE(pic), GTK_CONTENT_FIT_COVER);

    // Create and configure a GtkBox to work as a wrapper
    sideBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(sideBox, TRUE);
    gtk_widget_set_vexpand(sideBox, TRUE);

    // Create and configure application name label
    nameLabel = gtk_label_new(APPLICATION_NAME);
    gtk_widget_add_css_class(nameLabel, "nameLabel");
    gtk_widget_set_valign(nameLabel, GTK_ALIGN_START);

    // Create and configure the GtkBox which will contain GtkButtons
    btnBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_vexpand(btnBox, TRUE);
    gtk_box_set_spacing(GTK_BOX(btnBox), 45);
    gtk_widget_set_halign(btnBox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(btnBox, GTK_ALIGN_CENTER);

    // Create GtkButtons
    btnCreate = gtk_button_new_with_label("Create");
    btnRead = gtk_button_new_with_label("Read");
    btnUpdate = gtk_button_new_with_label("Update");
    btnExit = gtk_button_new_with_label("Exit");

    // Add css class to widgets
    gtk_widget_add_css_class(sideBox, "sideBox");
    gtk_widget_add_css_class(btnCreate, "button");
    gtk_widget_add_css_class(btnRead, "button");
    gtk_widget_add_css_class(btnUpdate, "button");
    gtk_widget_add_css_class(btnExit, "button");

    // Bind GtkButtons with signal handlers
    g_signal_connect(btnExit, "clicked", G_CALLBACK(closeWindow), win);

    // Append widgets
    gtk_window_set_child(GTK_WINDOW(win), mainBox);
    gtk_box_append(GTK_BOX(mainBox), scrolledWin);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWin), pic);
    gtk_box_append(GTK_BOX(mainBox), sideBox);
    gtk_box_append(GTK_BOX(sideBox), nameLabel);
    gtk_box_append(GTK_BOX(sideBox), btnBox);
    gtk_box_append(GTK_BOX(btnBox), btnCreate);
    gtk_box_append(GTK_BOX(btnBox), btnRead);
    gtk_box_append(GTK_BOX(btnBox), btnUpdate);
    gtk_box_append(GTK_BOX(btnBox), btnExit);

    gtk_window_present(GTK_WINDOW(win));
}

GtkApplication* admin_menu_new(void) {
    GtkApplication *app;

    app = gtk_application_new("com.github.abhishek01s.leydata", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    return app;
}