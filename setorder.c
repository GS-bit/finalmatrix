#include <string.h>
#include <gtk/gtk.h>
#include "validation.h"
#include "helpmenu.h"
#include "mainwindow.h"

void set_order(GtkWidget *btn, gpointer data);

void show_set_order_window(){
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Finalmatrix");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	GtkWidget *menubar;
	menubar = gtk_menu_bar_new();
	
	GtkWidget *helpmenu;
	helpmenu = get_help_menuitem();
	
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), helpmenu);
	
	GtkWidget *intro;
	intro = gtk_label_new("Defina a ordem do sistema de equações:");
	
	GtkWidget *entry;
	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry), 2);
	g_signal_connect(entry, "activate", G_CALLBACK(set_order), entry);
	
	GtkWidget *btn;
	btn = gtk_button_new_with_label("OK");
	g_signal_connect(btn, "clicked", G_CALLBACK(set_order), entry);
		
	GtkWidget *vbox;
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	
	gtk_box_pack_start(GTK_BOX(vbox), menubar, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), intro, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);
	
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_widget_show_all(window);
	
	gtk_main();
}


void set_order(GtkWidget *btn, gpointer data){
	if(is_valid_order(gtk_entry_get_text(GTK_ENTRY(data)))){
		int order = atoi(gtk_entry_get_text(GTK_ENTRY(data)));
		gtk_widget_destroy(gtk_widget_get_toplevel(btn));
		show_mainwindow(order);
	}
	
	else{
		GtkWidget *dialog;
		dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Erro: número inválido");
		
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
}
