/*
Name:			CPlotLib

Created in:		02/feb/2019
Last edited:	03/feb/2019

Created by:		Adailton Braga Júnior
E-mail:			adailtonjn68@gmail.com

*/

#ifndef CPLOTLIB_H_
#define CPLOTLIB_H_

#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct {
	GtkWidget *plot_area;
	double *x;
	double *y[10];
	unsigned char nplots;
	unsigned int N;
	char title[50];
} Plot2dTypeDef;

void cplotlib_init();
void plot_show();
void plot2d_init(Plot2dTypeDef *plot_struct, unsigned int N, unsigned char nplots);
void plot2d(Plot2dTypeDef *plot_struct);
void draw2d(GtkWidget *widget, cairo_t *cr, gpointer data);
double min(double *x, int N);
double max(double *x, int N);
int relativePoint(double x,double a, int b);


#endif
