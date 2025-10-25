#include "leydata.h"

int main(int argc, char **argv){
    GtkApplication *app;
    int stat;

    app = admin_menu_new();
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return stat;
}
