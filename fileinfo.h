#ifndef FILEINFO_H
#define FILEINFO_H
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "terrain.h"
#include "parse.h"
#include "name.h"
#include "window.h"
#include "chars.h"
#include "colors.h"
#include "initial.h"
#include "rule.h"

using namespace std;

class FileInfo
{
    //Name of the game. Size will be adjusted later
    string name;
    //Rule value for a Elementary file
    int rule;
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
    //l for life file, w for wireworld, and e for elementary. Throws an error otherwise
    char filetype;
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
    //Object containing flags for finding keywords and values of input file
    Parse *p;

    public:
        FileInfo();

        /*Checks to see if any keyvalues
         *were overwritten by user input
         *at the command line*/
        /*flag - Contains keyvalues parsed from
         *the command line*/
        void override(int txh,int txl,int tyh,int tyl,int wxh,int wxl,int wyh,int wyl);

        /*Loops through command line argument to find the
         *first successfully opened file given. If no file is found,
         *then takes standard input as file*/
        void openFile(int,const char*[]);

        /*Calls the proper display function to display file information*/
        void display();


        inline char getFileType(){
            return filetype;
        }
        inline int getRule(){
            return rule;
        }
        inline int getTxLow(){
            return txRangeLow;
        }
        inline int getTxHigh(){
            return txRangeHigh;
        }
        inline int getTyLow(){
            return tyRangeLow;
        }
        inline int getTyHigh(){
            return tyRangeHigh;
        }
        inline int getWxLow(){
            return wxRangeLow;
        }
        inline int getWxHigh(){
            return wxRangeHigh;
        }
        inline int getWyLow(){
            return wyRangeLow;
        }
        inline int getWyHigh(){
            return wyRangeHigh;
        }
        inline int* getAliveCoor(){
            return Acoor;
        }
        inline int* getOneCoor(){
            return Ocoor;
        }
        inline int* getHeadCoor(){
            return Hcoor;
        }
        inline int* getTailCoor(){
            return Tcoor;
        }
        inline int* getWireCoor(){
            return Wcoor;
        }
        inline int getACoordLen(){
            return AcoordLen;
        }
        inline int getHCoordLen(){
            return HcoordLen;
        }
        inline int getTCoordLen(){
            return TcoordLen;
        }
        inline int getWCoordLen(){
            return WcoordLen;
        }
        inline int getOCoordLen(){
            return OcoordLen;
        }
        inline int* getAliveColor(){
            return Acolor;
        }
        inline int* getDeadColor(){
            return Dcolor;
        }
        inline int* getEmptyColor(){
            return Ecolor;
        }
        inline int* getWireColor(){
            return Wcolor;
        }
        inline int* getHeadColor(){
            return Hcolor;
        }
        inline int* getTailColor(){
            return Tcolor;
        }
        inline int* getZeroColor(){
            return Zcolor;
        }
        inline int* getOneColor(){
            return Ocolor;
        }
        inline char getAliveCh(){
            return alive;
        }
        inline char getDeadCh(){
            return dead;
        }
        inline char getEmptyCh(){
            return empty;
        }
        inline char getWireCh(){
            return wire;
        }
        inline char getHeadCh(){
            return head;
        }
        inline char getTailCh(){
            return tail;
        }
        inline char getZeroCh(){
            return zero;
        }
        inline char getOneCh(){
            return one;
        }
        inline const char* getName(){
            return name.c_str();
        }


    private:

        /*Initializes all members of class*/
        void init();

        /*Writes a string to the temp file making sure to
         *add the character c to the string before this.
         *temp - file to be written to
         *buffer - string to used
         *c - character to be added to string*/
        void print(FILE* temp,string buffer,char c);

        /*Writes the information from the given file
         *to a new file without comments and new lines after
         *every ; and {.
         *FILE* - file to be compacted*/
        void compactFile(FILE*);

        /*Parses an array of bytes from the compacted file
         *and identifies keyvalues and keywords*/
        /*size - size of charList*/
        void parse();

        /*Checks that an identifier has only been
         *defined once. If defined more than once, throws
         *an exception*/
        void checkIDs(string str);

        /*Checks keyvalues. Throws an exception
         *if any necessary values are zero or null*/
        void checkKeyValues();

        /*Assumes first line of our compacted
         *file contains the file type. Checks the type and throws
         *an error if not a valid type. If valid, sets filetype character
         *to e for elementary, l for life and w for wireworld*/
        void checkFileType(string str);

        /*Displays file information for a life file*/
        void displayLife();

        /*Displays file information for a wireworld file*/
        void displayWireWorld();

        /*Displays file information for a elementary file*/
        void displayElementary();
};

#endif // FILEINFO_H
