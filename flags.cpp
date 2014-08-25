#include "flags.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;


Flags::Flags()
{
    fileOutput = false;
    visualOutput = false;
    help = false;
    controls = false;
    gen = 0;
    size = 10;
    txRangeHigh = 0;
    txRangeLow = 0;
    tyRangeHigh = 0;
    tyRangeLow = 0;
    wxRangeHigh = 0;
    wxRangeLow = 0;
    wyRangeHigh = 0;
    wyRangeLow = 0;
}

void Flags::parse(int argc,const char* agv[])
{
    int high = 0;
    int low = 0;

    for(int i=1;i<argc;i++)
    {
        if((i+1)<argc && strcmp(agv[i],"-s")==0)
            sscanf(agv[++i],"%d",&size);
        if(strcmp(agv[i],"-f")==0)
            fileOutput = true;
        if(strcmp(agv[i],"-h")==0)
            help = true;
        if(strcmp(agv[i],"-v")==0)
            visualOutput = true;
        if(strcmp(agv[i],"-c")==0)
            controls = true;
        if((i+1)<argc && strcmp(agv[i],"-g")==0)
            sscanf(agv[++i],"%d",&gen);
        if((i+1)<argc && strcmp(agv[i],"-tx")==0)
        {
            sscanf(agv[++i],"%d..%d",&low,&high);
            txRangeHigh = high;
            txRangeLow = low;
        }
        if((i+1)<argc && strcmp(agv[i],"-ty")==0)
        {
            sscanf(agv[++i],"%d..%d",&low,&high);
            tyRangeHigh = high;
            tyRangeLow = low;
        }
        if((i+1)<argc && strcmp(agv[i],"-wx")==0)
        {
            sscanf(agv[++i],"%d..%d",&low,&high);
            wxRangeHigh = high;
            wxRangeLow = low;
        }
        if((i+1)<argc && strcmp(agv[i],"-wy")==0)
        {
            sscanf(agv[++i],"%d..%d",&low,&high);
            wyRangeHigh = high;
            wyRangeLow = low;
        }
    }
    check();
}


void Flags::check()
{
    if(wxRangeHigh==0 && wxRangeLow==0)
    {
        wxRangeHigh = txRangeHigh;
        wxRangeLow = txRangeLow;
    }
    if(wyRangeHigh==0 && wyRangeLow==0)
    {
        wyRangeHigh = tyRangeHigh;
        wyRangeLow = tyRangeLow;
    }
    if(size<0)
        size = 10;
    if(gen<0)
        gen = 0;
}


void Flags::display()
{

    printf("wxRange: %d..%d\n",wxRangeLow,wxRangeHigh);
    printf("wyRange: %d..%d\n",wyRangeLow,wyRangeHigh);
    printf("txRange: %d..%d\n",txRangeLow,txRangeHigh);
    printf("tyRange: %d..%d\n",tyRangeLow,tyRangeHigh);
    printf("Generation: %d\n",gen);
}

