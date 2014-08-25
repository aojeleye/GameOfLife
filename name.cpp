#include "name.h"

Name::Name(string arr)
{
    name = "";
    buffer = arr;
    removeSpaces();
    setName();
}

void Name::setName()
{
    string str = "";
    int j = 0,q=0;
    bool add = false;

    for(int i = 0;i<buffer.length();i++)
        if(buffer[i]=='"')
            q++;
    if(q<2)
    {
        name = "";
        return;
    }
    while(true)
    {
        if(buffer[j]=='"')
            add = true;
        if(buffer[j]!='"' && add && buffer[j] !=';')
            str+= buffer[j];
        if(buffer[j]==';')
            break;
        j++;
    }
    name = str;
}

void Name::removeSpaces()
{
    string temp = "";
    bool quote = false;

    for(int i = 0;i<buffer.length();i++)
    {
        if(buffer[i] != ' ' && !quote)
            temp+=buffer[i];
        else if(quote)
            temp+=buffer[i];

        if(buffer[i]=='"')
             quote = true;
        if(buffer[i]==';')
            break;
    }
    buffer = temp;
}

