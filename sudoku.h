// Copyright (C) 2016 Adheesh Phadke
// This file is part of sudoku using gtk library.
//
// sudoku using gtk library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//See the GNU General Public License for more details.


#ifndef SUDOKU_H
#define SUDOKU_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUDOKU_SQUARE(s) ((Square *)(s))



GtkWidget *window;                 // parent for popup windows


int BLOCK_SIZE;             // NxN blocks within sudoku game
int GRID_SIZE;              // NxN sudoku game
int SQUARE_SIZE;            // sudoku square in pixels

int empty_squares;          // keeps track of when game is over
int game_started;

typedef struct SudokuSquare {
	GtkWidget *eventbox;
	GtkWidget *entry;
	GtkWidget *label;
	guint      editable : 1;
}Square;


struct {
	Square  **square;              // top left square of sudoku game
	Square   *last_square_clicked;
} sudoku;

/*
 * Opens up a modal dialog window with given TITLE and MESSAGE.
 */
void popup_msg(const char *title, const char *message);
/*
 * Triggered when user clicks a sudoku square. (button_press_event)
 * single click: Hides the last-clicked square's entry and brings the focus 
 *               to the square clicked.
 * @WIDGET the eventbox associated with a sudoku square
 * @DATA the sudoku square struct
 */
int on_click (GtkWidget *widget, GdkEventButton *event, gpointer data);

/*
 * Callback function when program is closed.
 * Frees up memory already allocated for **grid and **sudoku.square arrays.
 * And if gkt_main() has already begun, it then makes a call to gtk_main_quit().
 * @WIDGET not explicitly used, but is the main window's destroy callback
 * @DATA not used
 */
void on_close(GtkWidget *widget, gpointer data);
/*
 * Callback for ENTRY's backspace signal. Aside from erasing the text within
 * ENTRY, the text in the label associated with ENTRY's sudoku square is
 * also erased. Also ups the number of empty squares.
 * @ENTRY is a sudoku square's entry
 * @DATA not used
 */
void on_backspace(GtkEntry *entry, gpointer  data);
/*
 * Called by correct_sudoku() method to verify if each of the rows contain
 * all values (1-9 for regular sudoku). Returns true
 * if all rows check out, false otherwise.
 * @VALUES is an non-initialized array of size 9
 */
int rows_check_out(int *values);
/*
 * Called by correct_sudoku() method to verify if each of the cols contain
 * all values (1-9 for regular sudoku). Returns true
 * if all cols check out, false otherwise.
 * @VALUES is an non-initialized array of size 9
 */
int cols_check_out(int *values);
/*
 * Should be called when the number of empty squares is 0. Checks the status
 * of the sudoku grid. Returns true if the sudoku is correctly solved,
 * otherwise false. May also return false if there is insufficient memory, in
 * which case it also outputs the appropriate message to stderr.
 */
int correct_sudoku(void);
/*
 * Callback to each sudoku square's entry's insert-text signal. Allows only
 * proper values (1-9) to be displayed. Also updates the value shown 
 * if another value is inserted, e.g. user presses 3, then presses 7.
 * EDITABLE is updated after this function ends.
 * @EDITABLE is the entry associated with the sudoku square
 * @NUMBER is the value that is inserted by user
 * @LENGTH not used
 * @POSITION is an index corresponding to where the value is being inserted;
 * if this value is 1, then it is set back to 0 so that it replaces the current
 * value
 * @DATA is the sudoku square associated with EDITABLE
 */
void on_insert(GtkEditable *editable, gchar *number, gint length, gint *position, gpointer data);

int make_sudoku_board(GtkBox *box);

void solve_game(GtkToolButton *toolbutton, gpointer data);

void reset_game(GtkToolButton *toolbutton, gpointer data);

void make_toolbar(GtkBox *box);

int on_enter(GtkWidget *widget, GdkEvent *event, gpointer data);

int on_leave(GtkWidget *widget, GdkEvent *event, gpointer data);

#endif
