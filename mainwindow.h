#ifndef _H_MAINWINDOW
#define _H_MAINWINDOW
#include <gtk/gtk.h>
#include <string.h>
#include "resolutions.h"
#include "setorder.h"
#include "helpmenu.h"

void show_mainwindow(unsigned int n);
void calculate(GtkWidget *btn, gpointer *data);
void clear(GtkWidget *btn, gpointer *data);
void new_order(GtkWidget *btn, gpointer *data);

#endif

