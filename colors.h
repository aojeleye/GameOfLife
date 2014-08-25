#ifndef COLORS_H
#define COLORS_H
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Colors
{
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
    //string to have character information for a cell's color
    string buffer;

    public:
        Colors();

        /*Removes spaces from string
         *str - string containing character information for a cell's color*/
        void removeSpaces(string str);

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

    private:

        /*Sets the colors to their respective int arrays*/
        void setColors();

        /*Checks whether a valid color pixel value was read from
         *a file. Throws an error if not valid*/
        void check(int a,int b,int c);
};

#endif // COLORS_H
