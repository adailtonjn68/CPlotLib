#ifndef __PLOT_H
#define __PLOT_H

#include <gtk/gtk.h>

typedef struct {
	GtkWidget *plot_area;
	double *x;
	double *y;
	int N;
	
} PlotTypeDef;

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

int relativePoint(double x,double a, int b) {
	return ( a * x + b);
}

void draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	
	
	PlotTypeDef *plot_struct = data;
	double ymin = min(plot_struct->y, plot_struct->N);
	double ymax = max(plot_struct->y, plot_struct->N);
	double xmin = min(plot_struct->x, plot_struct->N);
	double xmax = max(plot_struct->x, plot_struct->N);
	
	// Get window size
	int X = gtk_widget_get_allocated_width(widget);
	int Y = gtk_widget_get_allocated_height(widget);
	
	// Define plot area boundaries inside drawing area
	int Xleft = 0.1*X, Xright = 0.9*X;
	int Ytop = 0.1*Y, Ybottom = 0.9*Y;
	
	double xslope = (Xright - Xleft) / (xmax - xmin);
	double yslope = (Ytop - Ybottom) / (ymax - ymin);
	double xconst = -xslope*xmin + Xleft;
	double yconst = -yslope*ymin + Ybottom;
	
	// Set background colour (white)
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
	
	// Draw window (plot) boundary
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);
	cairo_move_to(cr, Xleft, Ytop);
	cairo_line_to(cr, Xright, Ytop);
	cairo_line_to(cr, Xright, Ybottom);
	cairo_line_to(cr, Xleft, Ybottom);
	cairo_line_to(cr, Xleft, Ytop);
	cairo_stroke(cr);
	
    // Plot
	cairo_set_source_rgb(cr, 0.2, 1, 0.5);
	cairo_move_to(cr, relativePoint(*(plot_struct->x), xslope, xconst),
					relativePoint(*(plot_struct->y), yslope, yconst));
	for(int i = 1; i<plot_struct->N; ++i) {
		cairo_line_to(cr, relativePoint(*(plot_struct->x + i), xslope, xconst),
					relativePoint(*(plot_struct->y+i), yslope, yconst));
	}
	
	cairo_stroke(cr);
	

	


	
	//printf("in draw struct %p\n", data);
	//printf("in draw x %p\n", plot_struct->x);
	//printf("in draw x[1] %lf\n", *(plot_struct->x + 3));
	//printf("in draw tentando x %p\n", plot_struct.x);
	//printf("gpointer %p\n", data);
	
}



#endif