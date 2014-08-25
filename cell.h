#ifndef CELL_H
#define CELL_H

#include <stdio.h>

class Cell
{
    /*ASCII art representation for this cell*/
    int pic;
    /*ASCII art for next iteration in the simulation*/
    int update;

    public:
        Cell();

        /*Sets ASCII art code*/
        /*c - art code to be set to this cell*/
       inline void set(int c){
           pic = c;
       }

       /*Sets c to update which will be the
        *next state the cell turns to after
        *one cycle*/
       inline void queue(int c){
           update = c;
       }

       /*Returns pic*/
       inline char get(){
           return pic;
       }
       /*Prints out ASCII art*/
       inline void display(){
               printf("%c",pic);
       }
        /*Updates the current pic character*/
       inline void updateCell(){
           pic = update;
       }

};

#endif // CELL_H
