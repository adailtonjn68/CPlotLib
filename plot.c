#include "plot.h"

void plot2d_init(Plot2dTypeDef *plot_struct, unsigned char nplots) {
	plot_struct->plot_area = gtk_drawing_area_new();
	g_signal_connect(plot_struct->plot_area, "draw", G_CALLBACK(draw2d), plot_struct);
	plot_struct->nplots = nplots;
	plot_struct->N = 0;
}

void plot2d(Plot2dTypeDef *plot_struct) {
	plot_struct->plot_area = gtk_drawing_area_new();
	g_signal_connect(plot_struct->plot_area, "draw", G_CALLBACK(draw2d), plot_struct);
}

void draw2d(GtkWidget *widget, cairo_t *cr, gpointer data) {
	// Get window size
	int X = gtk_widget_get_allocated_width(widget);
	int Y = gtk_widget_get_allocated_height(widget);

	// Define plot area boundaries inside drawing area
	int Xleft = 0.1*X, Xright = 0.9*X;
	int Ytop = 0.1*Y, Ybottom = 0.9*Y;

	// Recover original structure by using its pointer
	Plot2dTypeDef *plot_struct = data;

	for (unsigned char i = 0; i<plot_struct->nplots; ++i) {
		// Get max and min values from plot arrays
		double ymin = min(plot_struct->y[i], plot_struct->N);
		double ymax = max(plot_struct->y[i], plot_struct->N);
		double xmin = min(plot_struct->x, plot_struct->N);
		double xmax = max(plot_struct->x, plot_struct->N);

		/* Constants to translate and rescale values to the centre of the plot frame
		 The scale and translation is done by the formula
		 x_relative = a * x_real + b (where a = xslope and b = xconst)

		 This computation is done by calling relativePoint(x_real, a, b)
		 */
		double xslope = (Xright - Xleft) / (xmax - xmin);
		double yslope = (Ytop - Ybottom + 2) / (ymax - ymin);
		double xconst = -xslope*xmin + Xleft;
		double yconst = -yslope*ymin + Ybottom;

		// Plot
		cairo_set_source_rgb(cr, 1, 0, 0);
		cairo_set_line_width(cr, 3);
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
