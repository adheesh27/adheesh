# Project Title

Simple sudoku game written in c.

The program stores user data (control scheme, color options and sudoku database) in data.txt file. New data.txt is created during start up, if no such file exist in current directory.

## Getting Started

A c compiler with the #include<gtk/gtk.h> header file installed.


### Installing

Firstly update the software by typing: sudo apt-get update.

To install the gtk library , open terminal and type in the following:

apt-get install libgtk2.0-dev

This makes the library available for development.

Further it is required to install the following packages:

pkg-config --libs gtk+-2.0 
pkg-config --cflags gtk+-2.0

## Running the programme

To run the programme, the following needs to be typed:

gcc ****name of c file**** `pkg-config --libs gtk+-2.0` `pkg-config --cflags gtk+-2.0` or use the Makefile
and complile : make

### Functions yet to be complete

gensudoku(): which generates sudoku based on difficulty

generating the sudoku grid on the UI.

linking of functions to the gtk call back functions

