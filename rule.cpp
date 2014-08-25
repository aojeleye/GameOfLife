#include "rule.h"

Rule::Rule(string str)
{
    rule = 0;
    buffer = str;
    removeSpaces();
    setRule();
}

void Rule::setRule()
{
    int n = 0;
    sscanf((const char*)buffer.c_str(),"Rule=%d",&n);
    rule = n;
}

void Rule::removeSpaces()
{
    string temp = "";

    for(int i = 0;i<buffer.length();i++)
    {
        if(buffer[i] != ' ')
            temp+=buffer[i];
        if(buffer[i]==';')
            break;
    }
    buffer = temp;
}
