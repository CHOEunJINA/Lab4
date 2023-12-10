#include <gtk/gtk.h>

enum {
	COLUMN_TITLE,
	COLUMN_ARTIST,
	COLUMN_CATALOGUE,
	N_COLUMNS
};

void quit(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char *argv[]){
	GtkWidget *window;
	GtkTreeStore *store;
	GtkWidget *view;
	GtkTreeIter parent_iter, child_iter;
	GtkCellRenderer *renderer;
	
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Tree");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	g_signal_connect(window, "destroy", G_CALLBACK(quit), NULL);
	
	store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_store_append(store, &parent_iter, NULL);
	gtk_tree_store_set(store, &parent_iter, COLUMN_TITLE, "Again", COLUMN_ARTIST, "DEAN", COLUMN_CATALOGUE, "A221210", -1);
	gtk_tree_store_append (store, &child_iter, &parent_iter);
	gtk_tree_store_set (store, &child_iter, COLUMN_TITLE, "instagram", -1);
	
	view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW(view), COLUMN_TITLE, "title",renderer, "text", COLUMN_TITLE, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),COLUMN_ARTIST,"artist", renderer, "text", COLUMN_ARTIST, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view), COLUMN_CATALOGUE,"catalogue", renderer, "text", COLUMN_CATALOGUE, NULL);
	gtk_container_add(GTK_CONTAINER(window), view);
	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}
