#include "plot.h"


void cplotlib_init() {
	gtk_init(NULL, NULL);
}

void plot2d_init(Plot2dTypeDef *plot_struct, unsigned int N, unsigned char nplots) {
/* plot2d_init(...) is responsible for creating a Gtk drawing area widget, assign
a callback function and making the initial plot configurations.
 */
 	if(N<=0 || nplots<1) exit(1);

	plot_struct->plot_area = gtk_drawing_area_new(); // Create Gtk drawing area
	g_signal_connect(plot_struct->plot_area, "draw", G_CALLBACK(draw2d), plot_struct);
	plot_struct->nplots = nplots;
	plot_struct->N = N;
}


void plot2d(Plot2dTypeDef *plot_struct) {
	GtkWidget *frame;
	GtkWidget *window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), plot_struct->title);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	frame = gtk_frame_new(NULL);
	gtk_container_add(GTK_CONTAINER(window), frame);
	gtk_container_add(GTK_CONTAINER(frame), plot_struct->plot_area);

	gtk_widget_show_all (window);
}

void plot_show() {
	gtk_main ();
}

void draw2d(GtkWidget *widget, cairo_t *cr, gpointer data) {
	// Recover original structure by using its pointer
	Plot2dTypeDef *plot_struct = data;

	// Get window size
	int X = gtk_widget_get_allocated_width(widget);
	int Y = gtk_widget_get_allocated_height(widget);

	// Define plot area boundaries inside drawing area
	int Xleft = 0.1*X, Xright = 0.9*X;
	int Ytop = 0.1*Y, Ybottom = 0.9*Y;

	double yminGlobal = min(plot_struct->y[0], plot_struct->N);
	double ymaxGlobal = max(plot_struct->y[0], plot_struct->N);
	double xmin = min(plot_struct->x, plot_struct->N);
	double xmax = max(plot_struct->x, plot_struct->N);

	unsigned char i;
	for (i = 1; i<plot_struct->nplots; ++i) {
		// Get max and min values from plot arrays
		double ymin = min(plot_struct->y[i], plot_struct->N);
		double ymax = max(plot_struct->y[i], plot_struct->N);
		// double xmin = min(plot_struct->x, plot_struct->N);
		// double xmax = max(plot_struct->x, plot_struct->N);
		if (ymax > ymaxGlobal) ymaxGlobal = ymax;
		if (ymin < yminGlobal) yminGlobal = ymin;
	}

	for(i = 0; i<plot_struct->nplots; ++i) {
		/* Constants to translate and rescale values to the centre of the plot frame
		 The scale and translation is done by the formula
		 x_relative = a * x_real + b (where a = xslope and b = xconst)

		 This computation is done by calling relativePoint(x_real, a, b)
		 */
		double xslope = (Xright - Xleft) / (xmax - xmin);
		double yslope = (Ytop - Ybottom + 2) / (ymaxGlobal - yminGlobal);
		double xconst = -xslope*xmin + Xleft;
		double yconst = -yslope*yminGlobal + Ybottom;

		// Plot
		cairo_set_source_rgb(cr, 1, 0, 0);
		cairo_set_line_width(cr, 1);
		cairo_move_to(cr, relativePoint(*(plot_struct->x), xslope, xconst),
						relativePoint(*(plot_struct->y[i]), yslope, yconst));
		for(int k = 1; k<plot_struct->N; ++k) {
			cairo_line_to(cr, relativePoint(*(plot_struct->x + k), xslope, xconst),
						relativePoint(*(plot_struct->y[i]+k), yslope, yconst));
		}

		cairo_stroke(cr);
	}

	// Set background colour (white)
	// cairo_set_source_rgb(cr, 1, 1, 1);
	// cairo_paint(cr);

	// Draw plot frame
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);
	cairo_move_to(cr, Xleft, Ytop); 	// Top border
	cairo_line_to(cr, Xright, Ytop);	// Right border
	cairo_line_to(cr, Xright, Ybottom); // Bottom border
	cairo_line_to(cr, Xleft, Ybottom);	// Left border
	cairo_line_to(cr, Xleft, Ytop);
	cairo_stroke(cr);

	//printf("in draw struct %p\n", data);
	//printf("in draw x %p\n", plot_struct->x);
	//printf("in draw x[1] %lf\n", *(plot_struct->x + 3));
	//printf("in draw tentando x %p\n", plot_struct.x);
	//printf("gpointer %p\n", data);
}

int relativePoint(double x,double a, int b) {
	return (a * x + b);
}

double min(double *x, int N) {
	double res = x[0];
	for(int i = 1; i<N; ++i) {
		if (x[i]<res) res = x[i];
	}
	return res;
}

double max(double *x, int N) {
	double res = x[0];
	for(int i = 1; i<N; ++i) {
		if (x[i]>res) res = x[i];
	}
	return res;
}
