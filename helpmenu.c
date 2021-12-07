#include <gtk/gtk.h>

void show_about_dialog();

GtkWidget *get_help_menuitem(){
	GtkWidget *help;
	help = gtk_menu_item_new_with_label("Ajuda");
	
	GtkWidget *menu;
	menu = gtk_menu_new();
	
	GtkWidget *about;
	about = gtk_menu_item_new_with_label("Sobre");
	g_signal_connect(about, "activate", G_CALLBACK(show_about_dialog), NULL);
	GtkWidget *exit;
	exit = gtk_menu_item_new_with_label("Sair");
	g_signal_connect(exit, "activate", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), about);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), exit);

	return help;
}

void show_about_dialog(){
	GError *error = NULL;
	GdkPixbuf *logo = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), "x-office-spreadsheet", 48, GTK_ICON_LOOKUP_USE_BUILTIN, &error);

	GtkWidget *aboutdialog;
	aboutdialog = gtk_about_dialog_new();
	
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(aboutdialog), logo);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(aboutdialog), "Finalmatrix");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutdialog), "0.1");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(aboutdialog), "Um programa para encontrar a matriz final usando o método de resolução de equações lineares Gauss-Jordan");
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(aboutdialog), GTK_LICENSE_LGPL_2_1_ONLY);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(aboutdialog), "Gabriel Soares");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(aboutdialog), "http://www.github.com/gs-bit");
	
	gtk_dialog_run(GTK_DIALOG(aboutdialog));
	gtk_widget_destroy(aboutdialog);
}
