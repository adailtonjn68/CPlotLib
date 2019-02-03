# CPlotLib
Simple ploting library implementation in C which has easy integration with Gtk. 

Compilation for example_1.c can be done with:
gcc  -o run.o -Wall main.c plot.c `pkg-config --cflags --libs gtk+-3.0` -lm
