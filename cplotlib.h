/*
Name:			CPlotLib

Created in:		02/feb/2019
Last edited:	08/mar/2019

Created by:		Adailton Braga Júnior
E-mail:			adailtonjn68@gmail.com

*/

#ifndef CPLOTLIB_H_
#define CPLOTLIB_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// #define ABS_(x)	((x>=0)? x : -(x))
// #define ROUND_(x)	(x>=0)? (int) (x + 0.5) : (int) (ABS(x) + 0.5)
#define ROUND_(x)	(int) (x + 0.5)

typedef struct {
	GtkWidget *plot_area;
	double *x;
	double *y[20];
	unsigned char nplots;
	unsigned int N;
	char title[75];
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
