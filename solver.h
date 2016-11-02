// Copyright (C) 2016 Adheesh Phadke
// This file is part of sudoku using gtk library.
//
// sudoku using gtk library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//See the GNU General Public License for more details.


#ifndef SOLVER_H
#define SOLVER_H

#include "sudoku.h"

int mark_incorrect_squares(void);

void verify_game(GtkToolButton *toolbutton, gpointer data);

void display_solution(void);

void solve (int show_solution);

void solve_game(GtkToolButton *toolbutton, gpointer data);

#endif
