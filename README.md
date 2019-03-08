# CPlotLib

CPlotLib is a plotting library written in Gtk+3.0 for the C programming language.

#### Features
- Functions for stand-alone plotting.
- Easy integration with Gtk applications (user can easily link the plots in his/her program).

#### Requirements
- Gtk+ (available: https://www.gtk.org/)



#### How to compile
Bellow is an example for compilation of **example01_-_simple_plot.c**
```
gcc -o run.o example01_-_simple_plot.c cplotlib.c `pkg-config --cflags --libs gtk+-3.0` -lm
```

#### Next implementation
- Grid
- Axis numbers
- Labels
- Subplots

#### Contact
You can get in touch using the following e-mail
adailtonjn68@gmail.com
