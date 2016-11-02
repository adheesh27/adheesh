// Copyright (C) 2016 Adheesh Phadke
// This file is part of sudoku using gtk library.
//
// sudoku using gtk library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//See the GNU General Public License for more details.



#include "solver.h"


int mark_incorrect_squares(void)
{
/*	int row;
        int col;
	const char *strval;
	char value_f[50];
	int at_least_one_incorrect = 0;

	for(row = 0; row < GRID_SIZE; ++row)
	for(col = 0; col < GRID_SIZE; ++col) {
		if(sudoku.square[row][col].editable) {
			strval=gtk_entry_get_text(GTK_ENTRY(sudoku.square[row][col].entry));
			if(*strval == '\0')
				continue;

			
				if(*strval == '0')
					continue;

			// mark it red
			snprintf(value_f, 50, "<span foreground=\"#bb0000\">%s</span>",
					strval);
			gtk_label_set_markup(
					GTK_LABEL(sudoku.square[row][col].label), value_f);
			at_least_one_incorrect = 1;
	} }
	return at_least_one_incorrect;*/
return 0;
}

void verify_game(GtkToolButton *toolbutton, 
				 gpointer       data)
{
	if(!game_started) return;
	solve(0);
}

void display_solution(void)
{
	/*int row;
	int col;
	char value[2];
	char label_f[50];

	for(row = 0; row < GRID_SIZE; ++row)
	for(col = 0; col < GRID_SIZE; ++col) {
		if(sudoku.square[row][col].editable) {
			value[1] = '\0';
			gtk_entry_set_text(GTK_ENTRY(sudoku.square[row][col].entry), value);
			snprintf(label_f, 50,
					"<span foreground=\"#009999\">%s</span>", 
					value);
			gtk_label_set_markup(
					GTK_LABEL(sudoku.square[row][col].label), label_f);
	} }*/
}

void solve(int show_solution)
{

/*int i,m=0,n=0,number,c,fixed;

mainallot:

for(m=row;m<9;m++)
	{
	n=col;
	while(n<9)
		{
		number=1;
		fixed=isfixed(icount,m,n);
		if(fixed==0)
			{
			allot:
			a[m][n]=number;
			c=check(m,n);
			if(c==0)
				{
				number++;
				if(number>9)
					{
					a[m][n]=0;
					if(n==0)
						{
						row=m-1; col=8;
						if(row<0)
						return(0);
						goto backadjust;
						}
					else
						{
						row=m; col=n-1;
						if(row<0 || col<0)
						return(0);
						goto backadjust;
						}
					}
				goto allot;
				}
			}
		n++;
		if(n>8)
		col=0;
		}
	}
return(1);

backadjust:

fixed=isfixed(icount,row,col);
if(fixed==0)
	{
	number=a[row][col];
	allot1:
	number++;
	a[row][col]=number;
	if(number>9)
		{
		a[row][col]=0;
		if(col==0)
			{
			row--; col=8;
			if(row<0)
			return(0);
			goto backadjust;
			}
		else
			{
			col--;
			if(col<0)
			return(0);
			goto backadjust;
			}
		}
	c=check(row,col);
	if(c==0)
	goto allot1;
	else
		{
		if(col==8)
			{
			row++;
			if(row>8)
			return(0);
			col=0;
			goto mainallot;
			}
		else
			{
			col++;
			if(col>8)
			return(0);
			goto mainallot;
			}
		}
	}
else
	{
	if(col==0)
		{
		row--; col=8;
		if(row<0)
		return(0);
		goto backadjust;
		}
	else
		{
		col--;
		if(col<0)
		return(0);
		goto backadjust;
		}
	}*/

}

void solve_game(GtkToolButton *toolbutton, 
				gpointer       data)
{
	

	game_started = 0;

	// disallow user from editing any square after calling solve
	if(sudoku.last_square_clicked != NULL 
	   && sudoku.last_square_clicked->editable) {
		gtk_widget_hide(sudoku.last_square_clicked->entry);
		gtk_widget_show(sudoku.last_square_clicked->label);
	}

	solve(1);
}
