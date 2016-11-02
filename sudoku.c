// Copyright (C) 2016 Adheesh Phadke
// This file is part of sudoku using gtk library.
//
// sudoku using gtk library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// See the GNU General Public License for more details.


#include "sudoku.h"
#include "solver.h"
#include "generator.h"


int on_click(GtkWidget *widget, GdkEventButton *event, gpointer data)
{


	if(sudoku.last_square_clicked != NULL && sudoku.last_square_clicked->editable) {
		gtk_widget_hide(sudoku.last_square_clicked->entry);
		gtk_widget_show(sudoku.last_square_clicked->label);
	}
		if(SUDOKU_SQUARE(data)->editable) {
			gtk_widget_hide(SUDOKU_SQUARE(data)->label);
			gtk_widget_show(SUDOKU_SQUARE(data)->entry);
			gtk_widget_grab_focus(SUDOKU_SQUARE(data)->entry);
			
			gtk_editable_select_region(
					GTK_EDITABLE(SUDOKU_SQUARE(data)->entry), 1, 1);
		}
		sudoku.last_square_clicked = data;
	
	return 0;
}

int on_enter(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_widget_set_state(data, GTK_STATE_PRELIGHT);
	gtk_widget_set_state(widget, GTK_STATE_PRELIGHT);
	return 0;
}

int on_leave(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_widget_set_state(data, GTK_STATE_NORMAL);
	gtk_widget_set_state(widget, GTK_STATE_NORMAL);
	return 0;
}

void popup_msg(const char *title, const char *message)
{
	GtkWidget *msg;
	GtkWidget *hbox;
	GtkWidget *label;

	msg = gtk_dialog_new_with_buttons(
			title,
			GTK_WINDOW(window),
			GTK_DIALOG_MODAL | GTK_DIALOG_NO_SEPARATOR, 
			GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(msg)->vbox), hbox);
	gtk_container_set_border_width(GTK_CONTAINER(hbox), 8);
	gtk_widget_show(hbox);

	label = gtk_label_new(message);
	gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);

	g_signal_connect(G_OBJECT(msg), "response", 
			G_CALLBACK(gtk_widget_destroy), NULL);
	gtk_widget_show(msg);
}

void on_close(GtkWidget *widget, gpointer data)
{
	 size_t row;

	for(row = 0; row < GRID_SIZE; ++row)
		free(sudoku.square[row]);
	free(sudoku.square);
	sudoku.last_square_clicked = NULL;

	gtk_main_quit();
}

void on_backspace(GtkEntry *entry, gpointer data)
{
	gtk_label_set_text(GTK_LABEL(SUDOKU_SQUARE(data)->label), "");
	++empty_squares;
}

int rows_check_out(int *values)
{
	 int row;
	 int col;
	const char *val;
	for(row = 0; row < GRID_SIZE; ++row) {
		for(col = 0; col < GRID_SIZE; ++col)
			values[col] = 0;
		for(col = 0; col < GRID_SIZE; ++col) {
			val = gtk_label_get_text(GTK_LABEL(sudoku.square[row][col].label));
			if(*val == '\0')
				return 0;
			switch(BLOCK_SIZE) {
			case 3: values[*val-'1'] = 1; break;
			case 4: if(isdigit(*val))
						values[*val-'0'] = 0;
					        break;
			}
		}
		for(col = 0; col < GRID_SIZE; ++col)
			if(!values[col])
				return 0;
	}
	return 1;
}

int cols_check_out(int *values)
{
	 int row;
	 int col;
	const char *val;
	for(col = 0; col < GRID_SIZE; ++col) {
		for(row = 0; row < GRID_SIZE; ++row)
			values[row] = 0;
		for(row = 0; row < GRID_SIZE; ++row) {
			val = gtk_label_get_text(GTK_LABEL(sudoku.square[row][col].label));
			if(*val == '\0')
				return 0;
			switch(BLOCK_SIZE) {
			case 3: values[*val-'1'] = 1; break;
			case 4: if(isdigit(*val))
						values[*val-'0'] = 1;
					        break;
		} }
		for(row = 0; row < GRID_SIZE; ++row)
			if(!values[row])
				return 0;
	}
	return 1;
}

int correct_sudoku(void)
{
	int *values = (int *)malloc(GRID_SIZE * sizeof(int));
	if(values == NULL) {
		fputs(" Out of memory!\n", stderr);
		return 0;
	}

	if(!rows_check_out(values))
		return 0;
	if(!cols_check_out(values))
		return 0;

	free(values);
	return 1;
}

void on_insert(GtkEditable *editable, 
			   gchar       *number, 
			   gint         length, 
			   gint        *position,
			   gpointer     data)
{
	char number_f[40];          

	if(BLOCK_SIZE == 3 && (*number == '0' || !isdigit(*number))) {
		*number = '\0'; return;
	}
	
	snprintf(number_f, 40, "<span foreground=\"#009999\">%s</span>", number);
	gtk_label_set_markup(GTK_LABEL(SUDOKU_SQUARE(data)->label), number_f);

	if(*position == 1) {
		*position = 0;
		gtk_editable_delete_text(editable, 0, 1);
	}
	else if(game_started) {
		--empty_squares;
		if(empty_squares == 0 && correct_sudoku()) {
			game_started = 0;
			popup_msg("Congratulaions","You have solved the puzzle!");
	} }
}



int make_sudoku_board(GtkBox *box)
{
	GtkWidget *board;           // table in which to place the sudoku squares
	GtkWidget *frame;           // placed around each sudoku square
	GtkWidget *vbox;
	 size_t row;        // sudoku square locations
	 size_t col;

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
		fputs(" Out of memory!\n", stderr);
		return 0;
	}
	for(row = 0; row < GRID_SIZE; ++row) {
		sudoku.square[row] = (Square*)malloc(GRID_SIZE * sizeof(Square));
		if(sudoku.square[row] == NULL) {
			fputs(" Out of memory!\n", stderr);
			return 0;
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

		sudoku.square[row][col].editable = 1;
	}
	// by default no square has focus
	sudoku.last_square_clicked = NULL;
	return 1;
}



void reset_game(GtkToolButton *toolbutton, 
				gpointer data)
{
	 int row;
	 int col;

	game_started = 0;
	empty_squares = 0;
	for(row = 0; row < GRID_SIZE; ++row)
	for(col = 0; col < GRID_SIZE; ++col) {
		if(sudoku.square[row][col].editable) {
			gtk_label_set_text(GTK_LABEL(sudoku.square[row][col].label), "");
			gtk_entry_set_text(GTK_ENTRY(sudoku.square[row][col].entry), "");
			++empty_squares;
	} }
	game_started = 1;
}

void about_game(GtkWidget *toolbutton, 
				gpointer data)
{
	GtkWidget *about_dialog;
	GtkWidget *vbox;
	GtkWidget *program_version;
	GtkWidget *label;

	about_dialog = gtk_dialog_new_with_buttons(
			"About", GTK_WINDOW(window),
			GTK_DIALOG_NO_SEPARATOR | GTK_DIALOG_MODAL,
			GTK_STOCK_CLOSE, GTK_RESPONSE_NONE,
			NULL);

	vbox = gtk_vbox_new(FALSE, 10);
	gtk_box_pack_start(
			GTK_BOX(GTK_DIALOG(about_dialog)->vbox), vbox, TRUE, TRUE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 8);
	gtk_widget_show(vbox);


	program_version = gtk_label_new("sudoku 0.0.1");
	gtk_box_pack_start(GTK_BOX(vbox), program_version, TRUE, TRUE, 0);
	gtk_widget_show(program_version);


	label = gtk_label_new("Adheesh Phadke \n MIS:111508002");
	gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);

	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_destroy(about_dialog);
}


void help_menu(GtkWidget *toolbutton, 
				gpointer data)
{
	GtkWidget *help_dialog;
	GtkWidget *vbox;
	GtkWidget *label1;

	help_dialog = gtk_dialog_new_with_buttons(
			"Help", GTK_WINDOW(window),
			GTK_DIALOG_NO_SEPARATOR | GTK_DIALOG_MODAL,
			GTK_STOCK_CLOSE, GTK_RESPONSE_NONE,
			NULL);

	vbox = gtk_vbox_new(FALSE, 10);
	gtk_box_pack_start(
			GTK_BOX(GTK_DIALOG(help_dialog)->vbox), vbox, TRUE, TRUE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 8);
	gtk_widget_show(vbox);


	label1 = gtk_label_new("**HOW TO PLAY**\n\n The classic Sudoku game involves a grid of 81 squares.\n"
                               "The grid is divided into nine blocks, each containing nine squares.\n"
                               "Each of the nine bloacks has to contain all the numbers 1-9 within its squares.\n" 
                               "Each number can only appear once in a row, column or box.\n"
                               "Every puzzle has just one correct solution.");
	gtk_box_pack_start(GTK_BOX(vbox), label1, TRUE, TRUE, 0);
	gtk_widget_show(label1);

	gtk_dialog_run(GTK_DIALOG(help_dialog));
	gtk_widget_destroy(help_dialog);
}


void make_toolbar(GtkBox *box)
{
	GtkWidget   *toolbar;
	GtkToolItem *new_btn;
	GtkToolItem *separator;
	GtkToolItem *verify_btn;
	GtkToolItem *clear_btn;
	GtkToolItem *solve_btn;
	GtkToolItem *about_btn;
        GtkToolItem *help_btn;

	toolbar = gtk_toolbar_new();
	gtk_widget_set_name(toolbar, "toolbar");
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_BOTH);
	gtk_box_pack_start(box, toolbar, TRUE, TRUE, 0);

	//------------------- new button ----------------
	new_btn = gtk_menu_tool_button_new_from_stock(GTK_STOCK_NEW);
	gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(new_btn), " Generate New Game");
	g_signal_connect(G_OBJECT(new_btn), "clicked",                            
			G_CALLBACK(generate_game), 0); 
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_btn, 0);
	gtk_widget_show(GTK_WIDGET(new_btn));

	separator = gtk_separator_tool_item_new();
	gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(separator), TRUE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, 1);
	gtk_widget_show(GTK_WIDGET(separator));

	//------------------- verify button ----------------
	verify_btn = gtk_tool_button_new_from_stock(GTK_STOCK_EXECUTE);
	g_signal_connect(G_OBJECT(verify_btn), "clicked",
			G_CALLBACK(verify_game), NULL);
	gtk_tool_button_set_label(GTK_TOOL_BUTTON(verify_btn), "Verify");
	gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(verify_btn), "Check Game");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), verify_btn, 2);
	gtk_widget_show(GTK_WIDGET(verify_btn));

        separator = gtk_separator_tool_item_new();
	gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(separator), TRUE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, 3);
	gtk_widget_show(GTK_WIDGET(separator));

	//------------------- clear button ----------------
	clear_btn = gtk_tool_button_new_from_stock(GTK_STOCK_CLEAR);
	g_signal_connect(G_OBJECT(clear_btn), "clicked", 
			G_CALLBACK(reset_game), NULL);
	gtk_tool_button_set_label(GTK_TOOL_BUTTON(clear_btn), "Reset");
	gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(clear_btn), "Reset Game");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), clear_btn, 4);
	gtk_widget_show(GTK_WIDGET(clear_btn));

        separator = gtk_separator_tool_item_new();
	gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(separator), TRUE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, 5);
	gtk_widget_show(GTK_WIDGET(separator));

	//------------------- solve button ----------------
	solve_btn = gtk_tool_button_new_from_stock(GTK_STOCK_APPLY);
	g_signal_connect(G_OBJECT(solve_btn), "clicked", 
			G_CALLBACK(solve_game), NULL);
	gtk_tool_button_set_label(GTK_TOOL_BUTTON(solve_btn), "Solve!");
	gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(solve_btn), "Solution");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), solve_btn, 6);
	gtk_widget_show(GTK_WIDGET(solve_btn));

        
        separator = gtk_separator_tool_item_new();
	gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(separator), TRUE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, 7);
	gtk_widget_show(GTK_WIDGET(separator));

	//------------------- help button ----------------
	help_btn = gtk_tool_button_new_from_stock(GTK_STOCK_HELP);
	g_signal_connect(G_OBJECT(help_btn), "clicked",
			G_CALLBACK(help_menu), NULL);
	gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(help_btn), "help");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), help_btn, 8);
	gtk_widget_show(GTK_WIDGET(help_btn));

        separator = gtk_separator_tool_item_new();
	gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(separator), TRUE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, 9);
	gtk_widget_show(GTK_WIDGET(separator));

	//------------------- about button ----------------
	about_btn = gtk_tool_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect(G_OBJECT(about_btn), "clicked",
			G_CALLBACK(about_game), NULL);
	gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(about_btn), "About");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), about_btn, 10);
	gtk_widget_show(GTK_WIDGET(about_btn));
       

	gtk_widget_show(toolbar);
}


int main(int argc, char *argv[])
{
        
	GtkWidget *vbox, *hbox;
	GtkWidget *eventbox_hbox;      //for customization
        
	gtk_init(&argc, &argv);

	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(
			G_OBJECT(window), "destroy", G_CALLBACK(on_close), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "sudoku");
	
        BLOCK_SIZE = 3; GRID_SIZE = 9; SQUARE_SIZE = 41;

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show(vbox);


	make_toolbar(GTK_BOX(vbox));

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
        
        


	gtk_widget_show(window);

	
	gtk_main();
	

	return 0;
}
