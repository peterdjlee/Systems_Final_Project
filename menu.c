#include <gtk/gtk.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

GtkWidget *view; /* TextView */

/* used for selecting the text */
GdkAtom sel_atom = GDK_SELECTION_CLIPBOARD;/* identify the requests menu handler will manage. */
GtkItemFactory *main_menu; /* Item factory creates a menu from array of itemfactory entries */

/* prototype */

void show_help(void);
void show_about(void);

#define MENU_NEW 1
#define MENU_OPEN 2
#define MENU_SAVE 3
#define MENU_SAVE_AS 4
#define MENU_CRUN 5
#define MENU_QUIT 6

static void menu_show(gpointer data, guint action, GtkWidget *widget)
{

    switch(action)
      {
      case MENU_NEW:
	if(save_if_modified())  /* call save if modified wen user opens a new file */
	  {
	    /* get all the current tag table n put them in the new buffer */
	    buf = gtk_text_buffer_new(gtk_text_buffer_get_tag_table(buf));
	    gtk_text_view_set_buffer(GTK_TEXT_VIEW(view), buf);
	    g_object_unref(G_OBJECT(buf));
            /* needed for freeing memory by the buffer wen a new buffer is created */
	  }
	break;
      case MENU_OPEN:
	if(save_if_modified())
        {
	  /* call save if modified wen user opens a new file */
	  buf = gtk_text_buffer_new(gtk_text_buffer_get_tag_table(buf));
	  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view), buf);

        /* needed for freeing memory by the buffer wen a new buffer is created */
	  g_object_unref(G_OBJECT(buf));
	  load_file(NULL);
	}
	break;
      case MENU_SAVE:
	save_file(filename);
	break;
      case MENU_SAVE_AS:
	save_file(NULL);
	break;
    case MENU_CRUN:
  compile_and_run("run.c");
  break;
      case MENU_QUIT:
	if(save_if_modified())            /* call save if modified when user opens a new file */
	  gtk_widget_destroy(window);
	break;
      }
}

/* actual menu creation */

GtkItemFactoryEntry menu_def[] =
  {
    { (char *)"/_File", NULL, NULL, 0, (char *)"<Branch>", NULL },
    { (char *)"/File/_New", (char *)"<control>N", menu_show, MENU_NEW, (char *)"<StockItem>", GTK_STOCK_NEW },
    { (char *)"/File/_Open...", (char *)"<control>O", menu_show, MENU_OPEN, (char *)"<StockItem>", GTK_STOCK_OPEN },
    { (char *)"/File/_Save", (char *)"<control>S", menu_show, MENU_SAVE, (char *)"<StockItem>", GTK_STOCK_SAVE },
    { (char *)"/File/Save _As...", NULL, menu_show, MENU_SAVE_AS, (char *)"<StockItem>", GTK_STOCK_SAVE_AS },
    { (char *)"/File/sep", NULL, NULL, 0, (char *)"<Separator>", NULL },
    { (char *)"/File/_Compile_&_Run", (char *)"<control>R", menu_show, MENU_CRUN, (char *)"<StockItem>", GTK_STOCK_OK },
    { (char *)"/File/sep", NULL, NULL, 0, (char *)"<Separator>", NULL },
    { (char *)"/File/_Quit", (char *)"<control>Q", menu_show, MENU_QUIT, (char *)"<StockItem>", GTK_STOCK_QUIT },
  };
