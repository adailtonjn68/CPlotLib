#include <math.h>
#include <gtk/gtk.h>
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

	GtkWidget *window;
	GtkWidget *frame;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "PLOT IN C");
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	frame = gtk_frame_new(NULL);
	gtk_container_add(GTK_CONTAINER(window), frame);

	int N = 10;
	double t[N], y[N];
	t[0] = 0;

	linspace(t, 2*PI, N);

	for(int i = 0; i<N; ++i) y[i] = sin(t[i]);

	Plot2dTypeDef plot1;
	plot1.N = N;
	plot1.x = t;
	plot1.y = y;
	plot2d(&plot1);

	gtk_container_add(GTK_CONTAINER(frame), plot1.plot_area);

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
