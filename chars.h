#ifndef CHARS_H
#define CHARS_H
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Chars
{
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
    //String to have character information for a cell
    string buffer;

    public:
        Chars();


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



        /*Removes spaces from string
         *str - string containing character information for a cell character*/
        void removeSpaces(string str);

    private:

        /*Parses buffer for a cell type keyword
         *then sets the corresponding variable
         *to the parsed character*/
        void setCha();

        /*Checks if parsed character is valid.
         *Throws an error if value is less than 0
         *or greater 255*/
        void check(int n);
};

#endif // CHARS_H
