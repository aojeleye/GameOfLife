#ifndef NAME_H
#define NAME_H
#include <stdio.h>
#include <string>

using namespace std;

class Name
{
    //String to be given name of simulation
    string name;
    //Line taken from file that contains name
    string buffer;

    public:
        /*Constructor that takes in a string
         *parses and stores the name information assuming
         *the name identfier is found
         *buffer - string containing name*/
        Name(string buffer);

        inline string get(){
            return name;
        }

    private:

        /*Sets the name of the simulation*/
        void setName();

        /*Removes spaces from string excluding
         *the ones between quotation marks*/
        void removeSpaces();


};

#endif // NAME_H
