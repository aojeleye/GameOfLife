#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <stdio.h>

using namespace std;

class Window
{
    //High value for x range
    int wxRangeHigh;
    //Low value for x range
    int wxRangeLow;
    //High value for y range
    int wyRangeHigh;
    //Low value for y range
    int wyRangeLow;
    //String to have range information
    string buffer;

    public:
        Window();

        inline int getXHigh(){
            return wxRangeHigh;
        }
        inline int getXLow(){
            return wxRangeLow;
        }
        inline int getYHigh(){
            return wyRangeHigh;
        }
        inline int getYLow(){
            return wyRangeLow;
        }

        /*Removes spaces from string
         *str - string containing range information*/
        void removeSpaces(string str);

      private:

        /*Sets the terrain range values to
         *respective variables via parsing buffer string*/
        void setWin();

};

#endif // WINDOW_H
