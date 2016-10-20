void generate_game(GtkWidget *toolbutton, 
				   GtkWidget *done_btn)
{
	if(designing_sudoku) {
		g_thread_create(clear_statusbar_msg, (gpointer)500000, FALSE, NULL);
		gtk_widget_set_sensitive(done_btn, FALSE);
		designing_sudoku = false;
	}
	clear_sudoku_grid();

	// disallow user from being able to edit a non-editable square after
	// a new game is generated
	if(sudoku.last_square_clicked != NULL
	   && sudoku.last_square_clicked->editable) {
		gtk_widget_hide(sudoku.last_square_clicked->entry);
		gtk_widget_show(sudoku.last_square_clicked->label);
	}

	generate_random_game();

	game_started = true;
}


void clear_sudoku_grid(void)
{
	register int row;
	register int col;

	for(row = 0; row < GRID_SIZE; ++row)
	for(col = 0; col < GRID_SIZE; ++col) {
		gtk_label_set_text(GTK_LABEL(sudoku.square[row][col].label), "");
		gtk_entry_set_text(GTK_ENTRY(sudoku.square[row][col].entry), "");
	}
	empty_squares = 0;
}


void solve_game(GtkToolButton *toolbutton, 
				gpointer       data)
{
	if(designing_sudoku)
		return;

	game_started = false;

	// disallow user from editing any square after calling solve
	if(sudoku.last_square_clicked != NULL 
	   && sudoku.last_square_clicked->editable) {
		gtk_widget_hide(sudoku.last_square_clicked->entry);
		gtk_widget_show(sudoku.last_square_clicked->label);
	}

	solve(TRUE);
}
