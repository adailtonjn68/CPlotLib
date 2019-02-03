#include <stdio.h>
#include <math.h>
#include "plot.h"

#define PI 3.141592654

void linspace(double *x0, double xf, int N) {
	double dt = (xf - *x0)/(N - 1);

	for(int k = 1; k < (N - 1); ++k) {
		x0[k] = x0[k-1] + dt;
	}
	x0[N - 1] = xf;
}

int main(int argc, char *argv[]) {

	// Generation of arrays to be plotted
	int N = 100;
	double t[N], y1[N], y2[N];
	t[0] = 0;

	linspace(t, 2*PI, N);

	for(int i = 0; i<N; ++i) {
		y1[i] = sin(t[i]);
		y2[i] = 0.5*exp(-0.5*t[i]);
	}

	// This is where the magic happens
	cplotlib_init();			// Initialize cplotlib
								// (only necessary if gtk_init() was not called yet).
	Plot2dTypeDef plot1, plot2;		// Create a plotting structure
	plot2d_init(&plot1, N, 1);	// Assign a Gtk drawing area to plot1, determine samples, and number of plots
	plot2d_init(&plot2, N, 1);
	strcpy(plot1.title, "Plot 1");	// (Only necessary if user wants to set a window title).
	strcpy(plot2.title, "Plot 2");
	plot1.x = t;		// Assign t[] to x axis
	plot2.x = t;
	plot1.y[0] = y1;	// Assign y1[] to y axis
	plot2.y[0] = y2;	// Assign y2[] to y axis
	plot2d(&plot1);		// Create a top level window for the plotting area
						// (only necessary if user wants a standalone window ).
	plot2d(&plot2);
	plot_show();		// Exhibit window (onlye necessary if user has not called gtk_main())

	return 0;
}
