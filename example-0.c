#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  // GtkWidget *button;
  // GtkWidget *button_box;

  GtkWidget *view;
  GtkTextBuffer *buffer;
  GtkTextIter start, end;
  PangoFontDescription *font_desc;
  GdkRGBA rgba;
  GtkTextTag *tag;
  GtkCssProvider *provider;
  GtkStyleContext *context;

  window = gtk_application_window_new (app);
  gtk_window_set_title(GTK_WINDOW(window), "Node");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 500);

  view = gtk_text_view_new ();
  gtk_container_add(GTK_CONTAINER(window), view);
  // button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  // gtk_container_add(GTK_CONTAINER(window), button_box);

  // Set the text
  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
  gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);

  provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_data (provider,
                                 "textview {"
                                 " font: 25 courier;"
                                 "  color: black;"
                                 "}",
                                 -1,
                                 NULL);
  context = gtk_widget_get_style_context (view);
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

/* Change left margin throughout the widget */
  gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view), 10);
  gtk_text_view_set_top_margin (GTK_TEXT_VIEW (view), 10);

  // Call print_hello if button clicked
  // button = gtk_button_new_with_label("Click me!");
  // g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  // g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  // gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all(window);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.lilee.myapp", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}
