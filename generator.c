// Copyright (C) 2016 Adheesh Phadke
// This file is part of sudoku using gtk library.
//
// sudoku using gtk library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//See the GNU General Public License for more details.



#include "generator.h"


int gen_solve(int smax)
{
/*int c,i,m,n,count=1,fixed,error;
int mode;
char choice;
randomize();
generate:
for(m=0;m<9;m++)
for(n=0;n<9;n++)
a[m][n]=0;
for(i=0;i<60;i++)
	{
	r[i][0]=20; r[i][1]=20;
	}

	
	
mode=27+random(2);
		 
sudoku.square[0][0]=1+random(8); r[0][0]=0; r[0][1]=0;
for(count=1;count<10;count++)
	{
	choose:
	m=random(9); n=random(9);
	fixed=isfixed(icount,m,n);
	if(fixed==1)
	goto choose;
	r[count][0]=m; r[count][1]=n;
	allot:
	sudoku.square[m][n]=1+random(9);
	if(sudoku.square[m][n]==0)
	goto allot;
	c=check(m,n);
	if(c==0)
	goto allot;
	}
icount=count;
error=solve();
for(m=0;m<9;m++)
for(n=0;n<9;n++)
b[m][n]=sudoku.square[m][n];
row=0; col=0;
for(i=0;i<60;i++)
	{
	r[i][0]=20; r[i][1]=20;
	}
if(error==0)
goto generate;
for(count=0;count<mode/2;count++)
	{
	choose2:
	m=random(9); n=random(5);
	fixed=isfixed(count,m,n);
	if(fixed==1)
	goto choose2;
	r[count][0]=m; r[count][1]=n;
	r[count+mode/2][0]=8-m;
	r[count+mode/2][1]=8-n;
	}
for(m=0;m<9;m++)
for(n=0;n<9;n++)
	{
	fixed=isfixed(mode,m,n);
	if(fixed!=1)
	sudoku.square[m][n]=0;
	}*/
return 0;
}


int init_all(void)
{
	

	return 1;
}

void free_all(void)
{
	
}

void display_new_game(void)
{
/*int fixed;
	int row;
	int col;
	int blk;
	char value[2];
	char value_f[50]; 
int icount=0;
for(row=0;row<10;row++)
	{
	if(row%3==0)
		{
		if(row!=0)
		for(blk=0;blk<45;blk++)
		if(row==9)
		goto end;
		}
	if(row%3!=0)
		{
            return 0;
	}
	else
	for(col=0;col<9;col++)
		{
		if(col%3==0)
			{
			if(a[row][col]==0)
				{
				for(blk=0;blk<4;blk++)
				}
			else
				{
				printf(a[row[col]);
				fixed=isfixed(icount,row,col);
				if(fixed==1)
				else
				printf(sudoku.square[row][col]);
				}
			}
		else
			{
			if(sudoku.square[row][col]==0)
			for(blk=0;blk<5;blk++)
			else
				{
				fixed=isfixed(icount,row,col);
				if(fixed==1)
				else
				printf(sudoku.square[row][col]);
				}
			}
		}


	

	blk = 1;
	for(row = 0; row < GRID_SIZE; ++row)
	for(col = 0; col < GRID_SIZE; ++col, ++blk) {
			gtk_entry_set_text(GTK_ENTRY(sudoku.square[row][col].entry), value);
			snprintf(value_f, 50, 
					"<span foreground=\"#000000\">%s</span>", value);
			gtk_label_set_markup(
					GTK_LABEL(sudoku.square[row][col].label), value_f);
			sudoku.square[row][col].editable = FALSE;
			continue;
		}
		sudoku.square[row][col].editable = TRUE;
		++empty_squares;
	}*/
}

void clear_sudoku_grid(void)
{
        int row;
	int col;

	for(row = 0; row < GRID_SIZE; ++row)
	for(col = 0; col < GRID_SIZE; ++col) {
		gtk_label_set_text(GTK_LABEL(sudoku.square[row][col].label), "");
		gtk_entry_set_text(GTK_ENTRY(sudoku.square[row][col].entry), "");
	}
	empty_squares = 0;
}

void generate_random_game(void)
{
	if(!init_all()) {
		fputs("Insufficient memory!\n", stderr);
		return;
	}
	
	display_new_game();

	free_all();
}

void generate_game(GtkWidget *toolbutton)
{
	
	clear_sudoku_grid();

	// disallow user from being able to edit a non-editable square after
	// a new game is generated
	if(sudoku.last_square_clicked != NULL
	   && sudoku.last_square_clicked->editable) {
		gtk_widget_hide(sudoku.last_square_clicked->entry);
		gtk_widget_show(sudoku.last_square_clicked->label);
	}

	generate_random_game();

	game_started = 1;
}
