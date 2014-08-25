README

I. Files
-------------
colors.cpp / colors.h
chars.cpp / chars.c
board.cpp / board.h
boardGUI.cpp / boardGUI.h
cell.cpp / cell.h
initial.cpp / initial.h
fileinfo.cpp / fileinfo.h
flags.cpp / flags.h
life.cpp / life.h
lifeGUI.cpp / lifeGUI.h
name.cpp / name.h
terrain.cpp / terrain.h
window.cpp / window.h
parse.cpp / parse.h
controlbox.cpp / controlbox.h

A. colors

Handles parsing the input file for the pixel color values for all cells and stores the information.
Takes a string and parses it for the key values and returns
an stores them into respective int array. Throws an error for invalid pixel values.


B. chars

Handles parsing the input file for a character for all cells and stores  the information.
Takes a string and parses it for the key values and stores
the character into its respective variable. Throws an error if character is invalid.


C. board

Creates and processes a board of "cells" based on the information parsed
from the input file. First initializes an array of "cells" then sets the corresponding
cells to the given coordinates as alive. Then processes the board by the rules of the 
current simulation being ran and displays the board's cells in ASCII art representation.


D. boardGUI

Similar to board, creates and processes a board of "cells" based on the information parsed
from the input file. First initializes an array of "cells" then sets the corresponding
cells to the given coordinates as alive. Then processes the board by the rules of the 
current simulation being ran and draws a grid via GUI and matches the grid cells with board
(and coloring them their respective colors).


E. cell

Represents a cell in our cellular simulation programs. Contains the functionality to
set a character to a cell, queue another character then update the former character to
the queued one.


F. initial

Handles parsing the input file for the coordinates of initial set cells and stores information.
Takes a string and parses it for the key values and stores it into
an int array respective to string given. Throws an error if a coordinate is missing a value.


G. fileinfo

Parses the input file for keyvalues and stores them within this class. Starts by going
through the given file line by line and removes all comments. Writes them to a temp file.
Uses this temp file after writing to it and parses it for individual keyvalues via identifiers. Throws an 
error for duplicate identifiers, null keyvalues (pertaining to file type) and invalid file types.


H. flags

Parses the command line for valid flags and stores corresponding information within the class.
Also, parses the command line for a file argument and takes the first valid argument as a file if said
argument opens properly. If no file argument is detected, then standard input is used as the input file.


I. life

Contains a main function which handles the game simulation program and makes the necessary function calls to run the program. Passes on the user
arguments to the flags and fileinfo classes which are then passed to the board class
and outputs a helpscreen, formatted keyvalues and identifers or the
ASCII art representation of the current simulation depending on the user's input.


J. lifeGUI

Similar to the life class. Contains a main function which handles the game simulation program and makes the necessary function calls to run the program. Passes on the user
arguments to the flags and fileinfo classes which are then passed to the board and boardGUI class
and outputs a helpscreen or the GUI representation of the current simulation depending on the user's input.


K. name

Handles parsing the input file for a name string.
Takes a string in the constructor, searches it for the first " then stores the remaining characters into a string up util the next ".
Throws an error if more or less than 2 quotation marks are in the string.


L. terrain

Handles parsing the input file for the terrain range values. Takes a string and stores
the information after parsing it in the object.


M. window

Handles parsing the input file for the window range values. Takes a string and stores
the information after parsing it in the object.


N. controlbox

An extension of QDialog that essentially creates a dialog box with buttons and
spinboxes that manipulate the graphical representation of the board.



II. Programs
-------------
A. life

1. Purpose
The life program takes an input file and parses it for keyvalues and words. Depending on the file type, the program
calls the necessary functions to create a "board" filled with cells that will simulate a game. The details of the board
are determined by the parsed information from the input file. The rules of this game are determined by the file
type where each individual cell of the board will be processed every "generation" and may or may not change state depending on the rules.
For a "Life" file, an alive cell will die next cycle if it has less than 2 or more than 3 dead neighbors and a dead cell will remain dead
if it does not have exactly 3 alive neighbors. For a "WireWorld" file, a cell can either be a wire, head, tail, or empty.
If a cell is a wire, then next state it will be a head cell if one or two neightbors are head cells.
Otherwise remains a wire cell. If empty, then empty next state. If head then tail cell. If tail then wire cell. For an
elementary file, cells can either be zero or one. If a cell is a one then it stays a one. If a cell is a zero it may
become a one if its north, northwest, and northeast neighbors form the binary number that corresponds to a set bit
in the rule value. The size of the board is determined by the terrain values and the view of the board is determined by the window. 
If the view is bigger than the terrain then the extra space is filled with dead cells. This game simulation is represented by an ASCII art board.

2. Design
Generally idea was to split up the job for each identifier/keyvalue into individual classes. This way a giant class handling all the
keyvalues would be avoided. The "handling" classes would perform their job and store their respective values which the main class (fileinfo)
will grab from them. From there the board is created which takes the fileinfo object and uses the stored information to create the board.

3. Handling
Throws the aforementioned errors in the Files section.


B. life_gui

1. Purpose
Similar to the life program. The life program takes an input file and parses it for keyvalues and words. Depending on the file type, the program
calls the necessary functions to create a "board" filled with cells that will simulate a game. The details of the board
are determined by the parsed information from the input file. The rules of this game are determined by the file
type where each individual cell of the board will be processed every "generation" and may or may not change state depending on the rules.
For a "Life" file, an alive cell will die next cycle if it has less than 2 or more than 3 dead neighbors and a dead cell will remain dead
if it does not have exactly 3 alive neighbors. For a "WireWorld" file, a cell can either be a wire, head, tail, or empty.
If a cell is a wire, then next state it will be a head cell if one or two neightbors are head cells.
Otherwise remains a wire cell. If empty, then empty next state. If head then tail cell. If tail then wire cell. For an
elementary file, cells can either be zero or one. If a cell is a one then it stays a one. If a cell is a zero it may
become a one if its north, northwest, and northeast neighbors form the binary number that corresponds to a set bit
in the rule value. The size of the board is determined by the terrain values and the view of the board is determined by the window. If the view is bigger than the terrain
then the extra space is filled with dead cells. This game simulation is represented a GUI containing a drawn grid with colored cells for alive and dead respectively.

2. Design
Essentailly the same as life program. Generally idea was to split up the job for each identifier/keyvalue into individual classes. This way a giant class handling all the
keyvalues would be avoided. The "handling" classes would perform their job and store their respective values which the main class (fileinfo)
will grab from them. From there the board is created which takes the fileinfo object and uses the stored information to create the board. This board is then
passed on to the boardGUI class which essentially lays a drawn grid "on top of" the created board. Depending on switches given a controlbox object may be
created in which case the user can manipulate the graphical repsentation of the grid.

3. Handling
Throws the aforementioned errors in the Files section.
