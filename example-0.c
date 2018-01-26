#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}

void create_window (char *name, int type) {
    GtkWidget *window;

    GtkWidget *button;

    GtkWidget *view;
    GtkTextBuffer *buffer;
    GtkCssProvider *provider;
    GtkStyleContext *context;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), name);

    GdkScreen * screen = gtk_window_get_screen(GTK_WINDOW(window));
    int width;
    int height;
    width = gdk_screen_get_width(screen);
    height = gdk_screen_get_height(screen);

    gtk_window_set_default_size(GTK_WINDOW(window), width * 1/2, height * 1/2);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

    view = gtk_text_view_new ();
    gtk_container_add(GTK_CONTAINER(window), view);

    // button = gtk_button_new_with_label("button");
    // gtk_container_add(GTK_CONTAINER(window), button);

    // Set the text
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    if (type == 1) {
      gtk_text_buffer_set_text (buffer, "Take notes here", -1);
      provider = gtk_css_provider_new ();
      gtk_css_provider_load_from_data (provider,
                                     "textview {"
                                     " font: 25px helvetica;"
                                     "  color: black;"
                                     "}",
                                     -1,
                                     NULL);
    } else if (type == 2) {
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
      gtk_text_buffer_set_text (buffer, "Type code here", -1);
      provider = gtk_css_provider_new ();
      gtk_css_provider_load_from_data (provider,
                                     "textview {"
                                     " font: 25px courier;"
                                     "  color: black;"
                                     "}",
                                     -1,
                                     NULL);
    } else if (type == 3) {
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
      gtk_window_set_default_size(GTK_WINDOW(window), width * 1/4, height * 1/4);
      gtk_text_buffer_set_text (buffer, "Compiled output", -1);
      provider = gtk_css_provider_new ();
      gtk_css_provider_load_from_data (provider,
                                     "textview {"
                                     " font: 25px courier;"
                                     "  color: black;"
                                     "}",
                                     -1,
                                     NULL);
      gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
      gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
    }

    context = gtk_widget_get_style_context (view);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view), 10);
    gtk_text_view_set_top_margin (GTK_TEXT_VIEW (view), 10);

    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (view), GTK_WRAP_CHAR);

    gtk_text_view_set_monospace (GTK_TEXT_VIEW (view), TRUE);

    gtk_widget_show_all(window);
}


int main (int argc, char **argv) {

      /* --- GTK initialization --- */
      gtk_init (&argc, &argv);

      create_window ("Node: Codes", 2);
      create_window ("Node: Notes", 1);
      create_window ("Node: Output", 3);

      gtk_main();
      exit(0);
}
