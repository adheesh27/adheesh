// Copyright (C) 2016 Adheesh Phadke
// This file is part of sudoku using gtk library.
//
// sudoku using gtk library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//See the GNU General Public License for more details.


#ifndef GENERATOR_H
#define GENERATOR_H

#include "sudoku.h"
//#include <time.h>

int gen_solve(int smax);

int init_all(void);

void free_all(void);

void make_grid(void);

void display_new_game(void);

void clear_sudoku_grid(void);

void generate_random_game(void);

void generate_game(GtkWidget *toolbutton);

#endif
