#ifndef TERRAIN_H
#define TERRAIN_H
#include <string>
#include <stdio.h>

using namespace std;

class Terrain
{
    //High value of x range for terrain
    int txRangeHigh;
    //Low value of x range for terrain
    int txRangeLow;
    //High value of y range for terrain
    int tyRangeHigh;
    //Low value of y range for terrain
    int tyRangeLow;
    //String to have range information
    string buffer;

    public:
        Terrain();

        inline int getXHigh(){
            return txRangeHigh;
        }
        inline int getXLow(){
            return txRangeLow;
        }
        inline int getYHigh(){
            return tyRangeHigh;
        }
        inline int getYLow(){
            return tyRangeLow;
        }

        /*Removes spaces from string
         *str - string containing range information*/
        void removeSpaces(string str);

     private:

        /*Sets the terrain range values
         *to their respective variable*/
        void setTer();

};

#endif // TERRAIN_H
