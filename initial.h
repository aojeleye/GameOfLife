#ifndef INITIAL_H
#define INITIAL_H
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Initial
{
    //String to have coordinate data
    string buffer;
    //Int array holding alive cell coordinate values
    int *alive;
    //Int array holding alive cell coordinate values
    int *one;
    //Int array holding alive cell coordinate values
    int *head;
    //Int array holding alive cell coordinate values
    int *tail;
    //Int array holding alive cell coordinate values
    int *wire;
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

    public:
        Initial();

        /*Removes spaces from string
         *str - string containing coordinate data*/
        void removeSpaces(string str);

        inline int* getAliveCoor(){
            return alive;
        }
        inline int* getOneCoor(){
            return one;
        }
        inline int* getHeadCoor(){
            return head;
        }
        inline int* getTailCoor(){
            return tail;
        }
        inline int* getWireCoor(){
            return wire;
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

    private:

        /*Reads the array for strings and
         *parses each one for the values which
         *are placed into their respective int array
         *arr - contains coordinate strings
         *len - lenght of string array*/
        void setCoord(string *arr,int len);

        /*Sets the coordinates into an array of
         *strings*/
        void setCoordString();

        /*Finds and returns the index of the first
         *coordinate*/
        int startPoint();

        /*Counts and returns the number of coordinates
         *via counting the number of (*/
        int numberOfCoords();

        /*Checks for valid number of
         *coordinates. Throws an error if not even
         *arr - arr of string coordinates
         *arrlen - length of arr*/
        void check(string *arr,int arrLen);
};

#endif // INITIAL_H
