#include "terrain.h"

Terrain::Terrain()
{
    txRangeHigh = 0;
    txRangeLow = 0;
    tyRangeHigh = 0;
    tyRangeLow = 0;
    buffer = "";
}

void Terrain::setTer()
{
    int low = 0;
    int high = 0;
    if(buffer.find("Xrange")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Xrange=%d..%d",&low,&high);
        txRangeHigh = high;
        txRangeLow = low;
    }
    else if(buffer.find("Yrange")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Yrange=%d..%d",&low,&high);
        tyRangeHigh = high;
        tyRangeLow = low;
    }
}

void Terrain::removeSpaces(string str)
{
    buffer = str;
    string temp = "";

    for(int i = 0;i<buffer.length();i++)
    {
        if(buffer[i] != ' ')
            temp+=buffer[i];
        if(buffer[i]==';')
            break;
    }
    buffer = temp;
    setTer();
}
