/* Usage:
 * cc draw-lines.c `pkg-config --cflags --libs gtk+-3.0` */

#include <cairo.h>
#include <gtk/gtk.h>

static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{
  do_drawing(cr);

  return FALSE;
}

static void do_drawing(cairo_t *cr)
{
	cairo_set_source_rgb(cr, 1.0, 1.0, 0);
  cairo_set_line_width(cr, 0.35);

	/* Wrong line :
	 * If I give a round y-value, the line width value will be set 2.0 (default),
	 * and the resulting line will has the alpha value like the line width 
	 * e.g. 0.35 */
	/*
	cairo_move_to(cr, 50, 50);
	cairo_line_to(cr, 250, 50);	
  cairo_stroke(cr);    
	*/

	/* (TRUE) Draw a yellow line with width 0.35:
	 * If I give a float number that contains a fractional part 
	 * e.g. 50.09 or 50.1, but not less than 0.09 like 50.01 or 50.08,
	 * cairo will draw the right line with the given width, 
	 * in the example is 0.35 */
	cairo_move_to(cr, 50, 50.09);
	cairo_line_to(cr, 250, 50.09);	
  cairo_stroke(cr);    
}

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);
 
  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL); 
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);  
       
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); 
  gtk_window_set_title(GTK_WINDOW(window), "Lines");
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}
