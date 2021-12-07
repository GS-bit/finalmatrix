#include <gtk/gtk.h>
#include <string.h>
#include "resolutions.h"
#include "validation.h"
#include "setorder.h"
#include "helpmenu.h"

GtkWidget *table_of_values[99][100]; /* Coefficients and independent values */
GtkWidget *mainwindow;

void calculate(GtkWidget *btn, gpointer *data);
void clear(GtkWidget *btn, gpointer *data);
void new_order(GtkWidget *btn, gpointer *data);

void show_mainwindow(unsigned int n){
	GtkWidget *vbox;
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	GtkWidget *grid;
	
	GtkWidget *menubar;
	menubar = gtk_menu_bar_new();
	
	GtkWidget *optionsmenu;
	optionsmenu = gtk_menu_item_new_with_label("Opções");
	
	GtkWidget *optionssubmenu;
	optionssubmenu = gtk_menu_new();
	
	GtkWidget *clear_option;
	clear_option = gtk_menu_item_new_with_label("Limpar");
	g_signal_connect(clear_option, "activate", G_CALLBACK(clear), &n);
	
	GtkWidget *new_order_option;
	new_order_option = gtk_menu_item_new_with_label("Nova ordem");
	g_signal_connect(new_order_option, "activate", G_CALLBACK(new_order), NULL);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(optionsmenu), optionssubmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(optionssubmenu), clear_option);
	gtk_menu_shell_append(GTK_MENU_SHELL(optionssubmenu), new_order_option);
		
	GtkWidget *helpmenu;
	helpmenu = get_help_menuitem();
	
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), optionsmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), helpmenu);
	
	GtkWidget *label_x[n][n]; /* x1, x2, x3... */
	GtkWidget *hbox[n][n]; /* containing coefficient 1 and x1, coefficient 2 and x2, coefficient 3 and x3... */
	
	GtkWidget *label_plus[n][n-1];
	GtkWidget *label_equal[n]; /* = */

	GtkWidget *calculate_btn;
	
	GtkWidget *warning_label;
	warning_label = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(warning_label), "<small>Aviso: números de ponto flutuante devem ser postos usando o ponto ( . ) como delimitador</small>");
	
	mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mainwindow), "Finalmatrix");
	gtk_window_set_resizable(GTK_WINDOW(mainwindow), FALSE);
	g_signal_connect(mainwindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);	

	grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
	
	GtkWidget *scrolledwindow;
	scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_propagate_natural_width(GTK_SCROLLED_WINDOW(scrolledwindow), TRUE);
    	gtk_scrolled_window_set_propagate_natural_height(GTK_SCROLLED_WINDOW(scrolledwindow), TRUE);
	
	/* Adding coefficients entries */
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			table_of_values[i][j] = gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(table_of_values[i][j]), 7);
			
			label_x[i][j] = gtk_label_new("x");
			char markup[32];
			snprintf(markup, 32, "x<sub>%d</sub>", i+1);
			gtk_label_set_markup(GTK_LABEL(label_x[i][j]), markup);

			hbox[i][j] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
			gtk_box_pack_start(GTK_BOX(hbox[i][j]), table_of_values[i][j], TRUE, TRUE, 1);
			gtk_box_pack_start(GTK_BOX(hbox[i][j]), label_x[i][j], FALSE, FALSE, 1);

			gtk_grid_attach(GTK_GRID(grid), hbox[i][j], 2*i, j, 1, 1);
		}
	}
	
	/* Adding "+" labels */
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n-1; j++){
			label_plus[i][j] = gtk_label_new("+");
			gtk_grid_attach(GTK_GRID(grid), label_plus[i][j], 2*j+1, i, 1, 1);
		}
	}
	
	/* Adding "=" labels */
	for(int i = 0; i < n; i++){
		label_equal[i] = gtk_label_new("=");
		gtk_grid_attach(GTK_GRID(grid), label_equal[i], n+n, i, 1, 1);
	}
	
	/* Adding independent terms entries */
	for(int i = 0; i < n; i++){
		table_of_values[i][n] = gtk_entry_new();
		gtk_entry_set_max_length(GTK_ENTRY(table_of_values[i][n]), 7);
		gtk_grid_attach(GTK_GRID(grid), table_of_values[i][n], n+n+1, i, 1, 1);
	}

	calculate_btn = gtk_button_new_with_label("Calcular");
	gtk_grid_attach(GTK_GRID(grid), calculate_btn, 0, n, 10, 1);
	
	g_signal_connect(calculate_btn, "clicked", G_CALLBACK(calculate), &n);
	
	gtk_widget_set_halign(grid, GTK_ALIGN_FILL);
	gtk_widget_set_valign(grid, GTK_ALIGN_FILL);
	
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), warning_label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);
	
	gtk_container_add(GTK_CONTAINER(scrolledwindow), vbox);
	
	gtk_container_add(GTK_CONTAINER(mainwindow), scrolledwindow);

	gtk_widget_show_all(mainwindow);

	gtk_main();
}

void calculate(GtkWidget* btn, gpointer *data){
	unsigned int *n = (unsigned int *) data;
	
	double system[(*n)][(*n)+1]; /* Array of the system */

	/* Adding coefficients in the array: */
	for(int i = 0; i < (*n); i++){
		for(int j = 0; j < (*n); j++){
			if(is_valid_coefficient(gtk_entry_get_text(GTK_ENTRY(table_of_values[j][i])))){
				system[i][j] = atof(gtk_entry_get_text(GTK_ENTRY(table_of_values[j][i])));
			}
			
			else{
				return;
			}
		}
	}
	
	/* Adding independent terms in the array: */
	for(int i = 0; i < (*n); i++){
		system[i][(*n)] = atof(gtk_entry_get_text(GTK_ENTRY(table_of_values[i][(*n)])));
	}
		
	gauss_jordan((*n), system);
	
	/* Showing coefficients in the window: */
	for(int i = 0; i < (*n); i++){
		for(int j = 0; j < (*n); j++){
			char value[32];
			snprintf(value, 32, "%f", system[i][j]);
			gtk_entry_set_text(GTK_ENTRY(table_of_values[j][i]), value);
		}
	}
	
	/* Showing independent terms in the window: */
	for(int i = 0; i < (*n); i++){
		char value[32];
		snprintf(value, 32, "%f", system[i][*(n)]);
		gtk_entry_set_text(GTK_ENTRY(table_of_values[i][(*n)]), value);
	}
	
}

void clear(GtkWidget *btn, gpointer *data){
	unsigned int *n = (unsigned int *) data;

	for(int i = 0; i < (*n); i++){
		for(int j = 0; j < (*n)+1; j++){
			gtk_entry_set_text(GTK_ENTRY(table_of_values[i][j]), "");
		}
	}
}

void new_order(GtkWidget *btn, gpointer *data){
	gtk_widget_destroy(mainwindow);
	show_set_order_window();
}
