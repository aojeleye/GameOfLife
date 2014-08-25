#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cell.h"
#include "fileinfo.h"
#include "flags.h"

class Board
{
    //l for life file, w for wireworld, and e for elementary.
    char filetype;
    //Rule number of elementary game simulation
    int rule;
    //Length of ruleArr array
    int ruleArrLen;
    //Terrain high end of x range
    int txRangeHigh;
    //Terrain low end of x range
    int txRangeLow;
    //Terrain high end of y range
    int tyRangeHigh;
    //Terrain low end of y range
    int tyRangeLow;
    //Window high end of x range
    int wxRangeHigh;
    //Window low end of x range
    int wxRangeLow;
    //Window high end of y range
    int wyRangeHigh;
    //Window low end of y range
    int wyRangeLow;
    //Total displacement for low to high for x range
    int txRange;
    //Total displacement for low to high for y range
    int tyRange;
    //Total displacement for low to high for x range
    int wxRange;
    //Total displacement for low to high for y range
    int wyRange;
    //Number of generations to cycle through
    int gen;
    // Int array holding pixel values for Dead color
    int *Dcolor;
    // Int array holding pixel values for Alive color
    int *Acolor;
    // Int array holding pixel values for Empty color
    int *Ecolor;
    // Int array holding pixel values for Head color
    int *Hcolor;
    // Int array holding pixel values for Wire color
    int *Wcolor;
    // Int array holding pixel values for Tail color
    int *Tcolor;
    // Int array holding pixel values for Zero color
    int *Zcolor;
    // Int array holding pixel values for One color
    int *Ocolor;
    //Character for alive cells
    char alive;
    //Character for dead cells
    char dead;
    //Character for empty cells
    char empty;
    //Character for wire cells
    char wire;
    //Character for head cells
    char head;
    //Character for tail cells
    char tail;
    //Character for zero cells
    char zero;
    //Character for one cells
    char one;
    //Int array holding alive cell coordinate values
    int *Acoor;
    //Int array holding alive cell coordinate values
    int *Ocoor;
    //Int array holding alive cell coordinate values
    int *Hcoor;
    //Int array holding alive cell coordinate values
    int *Tcoor;
    //Int array holding alive cell coordinate values
    int *Wcoor;
    //Length of coordinate array for alive cells
    int AcoordLen;
    //Length of coordinate array for one cells
    int OcoordLen;
    //Length of coordinate array for head cells
    int HcoordLen;
    //Length of coordinate array for tail cells
    int TcoordLen;
    //Length of coordinate array for wire cells
    int WcoordLen;
    //Length of  selected coordinate array for board (alive, wire, or one cell coordinates)
    int coorLen;
    //Number of set alive, one, or wire cells
    int numSetCells;
    //Number of set tail cells
    int numTailCells;
    //Number of set head cells
    int numHeadCells;
    //2D grid of cells
    Cell **grid;
    //2D window which represents how many cells are viewable by user
    Cell **window;
    //Contains values that correspond to the bits that are one for the rule value
    int* ruleArr;
    //Contains normalized coordinates for alive,wire, and one cells for window
    int* winCoor;
    //Contains normalized coordinates for head cells for window
    int* winHCoor;
    //Contains normalized coordinates for tail cells for window
    int* winTCoor;
    //Contains normalized coordinates for terrain for alive, wire, and one cells
    int* terCoor;
    //Contains normalized coordinates for terrain for head cells
    int* terHCoor;
    //Contains normalized coordinates for terrain for tail cells
    int* terTCoor;

    public:
        /*Constructor for board class that holds
         *a 2D Cell array and contains/handles the rule
         *for our game simulation
         *fi - object that contains keyvalues/words from input file
         *fl - object that contains switches and values from command line*/
        Board();
        Board(FileInfo fi,Flags fl);

        /*Runs simulation*/
        void run();

        /*Displays the state of the
         *Game of Life simulation in a ASCII art
         *board pattern. Only prints Terrain.*/
        void displayTerrain();

        /*Displays the state of the
         *Game of Life simulation in a ASCII art
         *board pattern. Only prints Window and terrain
         *that's included in it.*/
        void displayWindow();

        inline Cell** getBoard(){
            return window;
        }
        inline void setGen(int a){
            gen = a;
        }

     private:

        /*Checks if a coordinate was specified
         *to be a non-default cell(alive,wire,tail,head or one) with
         *respect to the terrain ranges. Returns true
         *if coordinates match the values in our
         *set cell arrays, false otherwise.*/
        char checkTerCoords(int y,int x);

        /*Checks if a coordinate was specified
         *to be a non-default cell(alive,wire,tail,head or one) with
         *respect to the window ranges. Returns true
         *if coordinates match the values in our
         *set cell arrays, false otherwise.*/
        char checkWinCoords(int y,int x);

        /*Initializes all members of the
         *Board class.*/
        void init(FileInfo fi,Flags fl);

        /*Initializes the 2D cell window array.
         *Determines the size of the array from the
         *given window ranges. Sets all equal coordinate
         *cells (that are in range) from grid to window.
         *If there are excess cells in window then sets those
         *to dead automatically.*/
        void setWindow();

        /*Handles the cases for an alive cell via
         *checking all surrounding neighbors.*/
        /*If less than 2 or more than 3 cell
        *neighbors are alive, then this current
        *cell(y,x) will die next cycle*/
        void aliveHandle(int y,int x);

        /*Handles the cases for a dead cell via
         *checking all surrounding neighbors.*/
        /*There must be exactly 3 alive
         *cell neighbors in order for this cell(y,x)
         *to be alive next cycle.*/
        void deadHandle(int y,int x);

        /*Handles rules for a wireworld file.
         *If a cell is empty, it will remain empty.
         *If a cell is a head, then becomes a tail.
         *If a cell is a tail, then becomes a wire.
         *If a cell is a wire, then stays a wire unless one
         *to two neighbors are heads in which cases becomes a head cell*/
        void wwHandle(int y,int x);

        /*Handles rules for a elementary file.
         *If a cell's north west, north, and north east neighbors
         *create a binary number that corresponds to a set bit of the
         *rule value(with respect to placement) then becomes a one cell.
         *So if the second bit is set for rule and the pattern above forms
         *001 then that cell will become a one cell. If a cell is already a one
         *cell, then stays as such.*/
        void elemHandle(int y,int x);

        /*Processes the cell via calling
         *the respective handling functions for
          the file type*/
        void processCells();

        /*"Normalizes" coordinates if the specified
         *ranges extend into the negative numbers.
         *Places the origin the lower left corner*/
        void normalizeTerrain();

        /*Sets the board up based on
         *parameters taken from constructor and
          finds set cells via checkTerCoords function*/
        void setGrid();

        /*Cycles through the board to simulate
         *"age" or passing of time by a set amount.
         *Accomplishes this by update each cell where
         *each one has been properly processed by
         *processCells()*/
        void age();

        /*Denormalizes coordinates(places origin in center
         *of grid) with respect to
         *the terrain ranges and stores the values into
         *window coordinate arrays.*/
        void denormalize();

        /*Normalizes window coordinates with respect to
         *the window ranges by placing the origin in the
         *lower left corner of grid*/
        void normalizeWindow();

        /*Finds the coordinates of set cells
         *in the grid. Stores coordinates in
         *window coordinate arrays*/
        void findSetCellCoor();

        /*Sets up the rules array by
         *locating the set bits in the rule value
         *and storing the placement number in the array*/
        void setRules();
};


#endif // BOARD_H
