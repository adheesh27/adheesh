#include<gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>



int main(int argc, char *argv[])
{
if (argc==1)
{
goto loop;
}

if(strcmp(argv[1], "-h") == 0){

printf("usage: gcc menu2.c `pkg-config --libs gtk+-2.0` `pkg-config --cflags gtk+-2.0` or make and then ./try");

return 0;
}

loop:

gtk_init(&argc,&argv); //initialize gtk
GtkWidget *window, *button, *vbox, *menu_bar, *game_menu, *help_menu; //declare widgets variables
GtkWidget *newgameMi;
GtkWidget *setMi;
GtkWidget *highMi;
GtkWidget *exitMi;
GtkWidget *aboutMi;
GtkWidget *howMi;
GtkWidget *GAME_MENU;
GtkWidget *SET_GAME;
GtkWidget *easy;
GtkWidget *medium;
GtkWidget *hard;
GtkWidget *sep;

window=gtk_window_new(GTK_WINDOW_TOPLEVEL);  //create window
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200); //size of the window
  gtk_window_set_title(GTK_WINDOW(window), "Sudoku");
g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);  //event when the window is closed using x

menu_bar=gtk_menu_bar_new(); 

 
GAME_MENU=gtk_menu_new();
game_menu=gtk_menu_item_new_with_label("Game"); 
                    


SET_GAME=gtk_menu_new();
setMi=gtk_menu_item_new_with_label("Set Game Difficulty");  
easy=gtk_menu_item_new_with_label("easy"); 
medium=gtk_menu_item_new_with_label("medium");
hard=gtk_menu_item_new_with_label("hard");  

gtk_menu_item_set_submenu(GTK_MENU_ITEM(setMi),SET_GAME);
gtk_menu_shell_append(GTK_MENU_SHELL(SET_GAME),easy);
gtk_menu_shell_append(GTK_MENU_SHELL(SET_GAME),medium);
gtk_menu_shell_append(GTK_MENU_SHELL(SET_GAME),hard);
sep=gtk_separator_menu_item_new();

newgameMi=gtk_menu_item_new_with_label("New Game");
highMi=gtk_menu_item_new_with_label("High Scores");
exitMi=gtk_menu_item_new_with_label("Exit");
 



  
gtk_menu_item_set_submenu(GTK_MENU_ITEM(game_menu),GAME_MENU);
gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),setMi);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),sep);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),newgameMi);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),sep);
//gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),highMi);
gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),sep);
gtk_menu_shell_append(GTK_MENU_SHELL(GAME_MENU),exitMi);
gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),game_menu);

g_signal_connect(G_OBJECT(exitMi), "activate",G_CALLBACK(gtk_main_quit), NULL);

//help_menu=gtk_menu_item_new_with_label("Help");                   
//gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),help_menu);
//gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);


//aboutMi=gtk_menu_item_new_with_label("About");             
//gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);

//howMi=gtk_menu_item_new_with_label("How To Play");             
//gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);

vbox=gtk_vbox_new(0,0);                                      
gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);

gtk_container_add(GTK_CONTAINER(window),vbox);
gtk_widget_show_all(window);

gtk_main();

return 0;
}
//help_menu=gtk_menu_new();

/*gboolean make_sudoku_board(GtkBox *box)
{
	GtkWidget *board;           // table in which to place the sudoku squares
	GtkWidget *frame;           // placed around each sudoku square
	GtkWidget *vbox;
	register size_t row;        // sudoku square locations
	register size_t col;

	// set up table
	board = gtk_table_new(GRID_SIZE, GRID_SIZE, TRUE);
	gtk_box_pack_start(GTK_BOX(box), board, TRUE, TRUE, 0);
	for(row = BLOCK_SIZE-1; row < GRID_SIZE; row += BLOCK_SIZE) {
		gtk_table_set_row_spacing(GTK_TABLE(board), row, 2);
		gtk_table_set_col_spacing(GTK_TABLE(board), row, 2);
	}
	gtk_widget_show(board);

	// allocate mem for sudoku squares
	sudoku.square = malloc(GRID_SIZE * sizeof(Square *));
	if(sudoku.square == NULL) {
		fputs("  * Out of memory!\n", stderr);
		return FALSE;
	}
	for(row = 0; row < GRID_SIZE; ++row) {
		sudoku.square[row] = (Square*)malloc(GRID_SIZE * sizeof(Square));
		if(sudoku.square[row] == NULL) {
			fputs("  * Out of memory!\n", stderr);
			return FALSE;
	} }

	// initialize sudoku squares
	for(row = 0; row < GRID_SIZE; ++row)
	for(col = 0; col < GRID_SIZE; ++col) {
		// set up the bordering frame for each sudoku square
		frame = gtk_frame_new(NULL);
		GTK_FRAME(frame)->shadow_type = GTK_SHADOW_IN;
		gtk_widget_set_size_request(frame, SQUARE_SIZE, SQUARE_SIZE);
		gtk_table_attach(GTK_TABLE(board), frame, row, row+1, col, col+1,
				GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
		gtk_widget_show(frame);

		// set up the eventbox
		sudoku.square[row][col].eventbox = gtk_event_box_new();
		gtk_widget_set_name(sudoku.square[row][col].eventbox, "sudoku_square");
		gtk_widget_set_events(sudoku.square[row][col].eventbox,
				GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
		gtk_container_add(GTK_CONTAINER(frame), 
				sudoku.square[row][col].eventbox);

		// set up vbox
		vbox = gtk_vbox_new(TRUE, 0);
		gtk_container_add(
				GTK_CONTAINER(sudoku.square[row][col].eventbox), vbox);
		gtk_widget_show(vbox);

		// set up label
		sudoku.square[row][col].label = gtk_label_new(NULL);
		gtk_widget_set_name(sudoku.square[row][col].label, "sudoku_label");
		gtk_box_pack_start(
				GTK_BOX(vbox), sudoku.square[row][col].label, TRUE, TRUE, 0);
		gtk_widget_show(sudoku.square[row][col].label);

		// set up the entry
		sudoku.square[row][col].entry = gtk_entry_new();
		gtk_widget_set_name(sudoku.square[row][col].entry, "sudoku_entry");
		gtk_entry_set_has_frame(
				GTK_ENTRY(sudoku.square[row][col].entry), FALSE);
		gtk_entry_set_width_chars(GTK_ENTRY(sudoku.square[row][col].entry), 1);
		gtk_entry_set_max_length(GTK_ENTRY(sudoku.square[row][col].entry), 1);
		gtk_entry_set_alignment(GTK_ENTRY(sudoku.square[row][col].entry), 0.5);
		gtk_box_pack_start(GTK_BOX(vbox), sudoku.square[row][col].entry, 
				TRUE, TRUE, 0);

		// set up signals now that eventbox and entry widgets have been created
		g_signal_connect(G_OBJECT(sudoku.square[row][col].entry),
				"backspace", G_CALLBACK(on_backspace), 
				SUDOKU_SQUARE(&sudoku.square[row][col]));
		g_signal_connect(G_OBJECT(sudoku.square[row][col].entry), 
				"insert-text", G_CALLBACK(on_insert), 
				SUDOKU_SQUARE(&sudoku.square[row][col]));
		g_signal_connect(G_OBJECT(sudoku.square[row][col].eventbox),
				"button_press_event", G_CALLBACK(on_click), 
				SUDOKU_SQUARE(&sudoku.square[row][col]));
		g_signal_connect(G_OBJECT(sudoku.square[row][col].eventbox), 
				"enter_notify_event", G_CALLBACK(on_enter), 
				sudoku.square[row][col].entry);
		g_signal_connect(G_OBJECT(sudoku.square[row][col].eventbox), 
				"leave_notify_event", G_CALLBACK(on_leave), 
				sudoku.square[row][col].entry);
		g_signal_connect(G_OBJECT(sudoku.square[row][col].entry), 
				"enter_notify_event", G_CALLBACK(on_enter), 
				sudoku.square[row][col].eventbox);
		g_signal_connect(G_OBJECT(sudoku.square[row][col].entry),
				"leave_notify_event", G_CALLBACK(on_leave), 
				sudoku.square[row][col].eventbox);

		gtk_widget_show(sudoku.square[row][col].eventbox);
		// do not show sudoku.square[row][col].entry

		sudoku.square[row][col].editable = TRUE;
	}
	// by default no square has focus
	sudoku.last_square_clicked = NULL;
	return TRUE;
}

int main(int argc, char *argv[])
{
	/////////////////GdkPixbuf *icon;
	GError *error = NULL;          // picks up image-loading errors
	GtkWidget *vbox, *hbox;
	GtkWidget *eventbox_statusbar; // for customization purposes (thru rc file)
	GtkWidget *eventbox_hbox;      // also for customization
	GtkToolItem *done;             // signals that user is done creating puzzle

	g_thread_init(NULL);
	gtk_init(&argc, &argv);

	//////////////gtk_rc_parse("gtk-sudoku.rc");

	///////////////////icon = gdk_pixbuf_new_from_file("images/sudoku-icon.png", &error);
	//////////////if(error == NULL)
		/////////////////regular_or_super_sudoku(icon);
	//////////else
		//////////regular_or_super_sudoku(NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(
			G_OBJECT(window), "destroy", G_CALLBACK(on_close), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "gtk-sudoku");
	if(error == NULL)
		gtk_window_set_icon(GTK_WINDOW(window), icon);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show(vbox);

	statusbar = gtk_statusbar_new();
	done = gtk_tool_button_new_from_stock(GTK_STOCK_JUMP_TO);
	g_signal_connect(G_OBJECT(done), "clicked",
			G_CALLBACK(user_done_creating), NULL);
	gtk_widget_set_sensitive(GTK_WIDGET(done), FALSE);
	gtk_box_pack_end(GTK_BOX(statusbar), GTK_WIDGET(done), FALSE, FALSE, 0);
	gtk_widget_show(GTK_WIDGET(done));

	make_toolbar(GTK_BOX(vbox), GTK_WIDGET(done));

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(hbox), 6);
	eventbox_hbox = gtk_event_box_new();
	gtk_widget_set_name(eventbox_hbox, "board");
	gtk_container_add(GTK_CONTAINER(eventbox_hbox), hbox);
	gtk_box_pack_start(GTK_BOX(vbox), eventbox_hbox, TRUE, TRUE, 0);
	gtk_widget_show(eventbox_hbox);
	gtk_widget_show(hbox);

	if(!make_sudoku_board(GTK_BOX(hbox))) {
		gtk_widget_destroy(window);
		exit(EXIT_FAILURE);
	}

	eventbox_statusbar = gtk_event_box_new();
	gtk_widget_set_name(eventbox_statusbar, "statusbar");
	gtk_container_add(GTK_CONTAINER(eventbox_statusbar), statusbar);
	gtk_box_pack_start(GTK_BOX(vbox), eventbox_statusbar, TRUE, TRUE, 0);
	gtk_widget_show(eventbox_statusbar);
	gtk_widget_show(statusbar);

	gtk_widget_show(window);

	//mutex = g_mutex_new();
	gtk_main();
	//g_mutex_free(mutex);

	return 0;
}*/
