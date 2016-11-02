TITLE: sudoku game generator and solver
 NAME: Adheesh Phadke
  MIS: 111508002

DESCRIPTION:This is a sudoku game where puzzles are generated randomly and displayed on the grid.
            Each box of the grid is allocated memory at the time of generation of the game.A 9X9 matrix( 2 - dimensional array)
            is used to store the numbers in the row and column wise form.

            The graphics library used for this purpose is "gtk".
            The "new" button on the display window generates a new puzzle everytime.
            The "verify" button checks the correctness of the entered value, and the puzzle 
            can be verified at every level.
            The "clear" button erases all the numbers which the user has put and clears the grid by deallocating memory
            occupied for each block.

**The project is not complete and the numbers do not show on the grid and hence the verify button does not work.
  Parts which affect the compiling of the code has been commented out.
              
    
(1) Running gtk-sudoku

To run this game, use the command: make all
This will compile the source files, after which you can simply run ./try


(2) Requirements:
	gcc compiler
	pkg-config tool
	GNU make
	GTK+ libraries

(3) Using gtk-sudoku

Clicking on a square will allow you to supply a number. Entering a number
is done through the keyboard. Depending on the game size, valid input is
1-9 (9x9 sudoku). Any other input is ignored.
You may change the value of the selected square simply by entering another
value, without having to first delete it.

(4) To Uninstall

The above instructions do not actually install the game on your machine; they 
simply compile the code and allow you to run the executable. If you no longer
wish to have this game existing on your hard drive then simply remove everything 
related to sudoku by typing : rm -rf try*


