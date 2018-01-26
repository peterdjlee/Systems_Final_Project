#include <gtk/gtk.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "fileselect.c"
#include "menu.c"

GtkWidget *view; /* text view widget where all the typing is done */

void create_window(char *name, int type) {
  GtkWidget *box, *scroll, *widget;
  GtkAccelGroup *accel;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(window), name);

  GdkScreen * screen = gtk_window_get_screen(GTK_WINDOW(window));
  int width;
  int height;
  width = gdk_screen_get_width(screen);
  height = gdk_screen_get_height(screen);

  gtk_window_set_default_size(GTK_WINDOW(window), width * 1/2, height * 1/2);

  box = gtk_vbox_new(FALSE, 0); /* create a container where the menus n text widget goes */
  /* false if u dont want extra padding in the box, 0 for spacing */

  /* add the box wid in the window */
  gtk_container_add(GTK_CONTAINER(window), box);

  /* create an accerelator for the item factory, keyboard shortcuts */
  accel = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel);

  /* Create a menu above the text view widget */
  main_menu = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<TextView>", accel);
  gtk_item_factory_create_items(main_menu,sizeof(menu_def) / sizeof(*menu_def),menu_def, NULL);

  /* Return the actual menu bar created by the item factory. */
  widget = gtk_item_factory_get_widget(main_menu, "<TextView>");

  /* put the menu in the menu container */
  gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);

  scroll = gtk_scrolled_window_new(NULL, NULL); /* put a scroll window widget */

  /* put the scroll window in the text container */
  gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);

  /* create the text view widget */
  view = gtk_text_view_new();

  /* create a buffer for the text view where everything gets stored */
  buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

  /* put the text widget in the scroll window */
  gtk_container_add(GTK_CONTAINER(scroll), view);


  gtk_widget_show_all(window); /* show all widgets in the window */
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);  /* gtk initializer can take filename as an argument*/

    create_window ("Node: Codes", 2);
    create_window ("Node: Notes", 1);
    create_window ("Node: Output", 3);

    /* load the file if a filename is specified */
    if(argc > 1)
	   load_file(g_strdup(argv[1]));

    /* the main loop where the app waits for mouse n keyboard events */
    gtk_main();

    return 0;
}
