#ifndef PLOT_H_
#define PLOT_H_

#include <gtk/gtk.h>

typedef struct {
	GtkWidget *plot_area;
	double *x;
	double *y;
	int N;

} Plot2dTypeDef;


void plot2d(Plot2dTypeDef *plot_struct);
void draw2d(GtkWidget *widget, cairo_t *cr, gpointer data);
double min(double *x, int N);
double max(double *x, int N);
int relativePoint(double x,double a, int b);


#endif
