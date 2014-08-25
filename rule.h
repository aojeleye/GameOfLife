#ifndef RULE_H
#define RULE_H
#include <stdio.h>
#include<iostream>
#include <string>

using namespace std;

class Rule
{
    //String to have rule information
    string buffer;
    //Rule value
    int rule;

    public:
        /*Constructor that parses and stores
         *rule value
         *buffer - string containing rule value*/
        Rule(string buffer);

        inline int get(){
            return rule;
        }

    private:

        /*Sets the name of the simulation*/
        void setRule();

        /*Removes spaces from string excluding
         *the ones between quotation marks*/
        void removeSpaces();
};

#endif // RULE_H
