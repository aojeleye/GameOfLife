#include "chars.h"

Chars::Chars()
{
    alive = 0;
    dead = 0;
    empty = 0;
    wire = 0;
    head = 0;
    tail = 0;
    zero = 0;
    one = 0;
    buffer = "";
}

void Chars::setCha()
{
    int n = 0;
    if(buffer.find("Alive")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Alive=%d;",&n);
        alive = n;
    }
    else if(buffer.find("Dead")!=-1)
    {
       sscanf((const char*)buffer.c_str(),"Dead=%d;",&n);
       dead = n;
    }
    else if(buffer.find("Empty")!=-1)
    {
       sscanf((const char*)buffer.c_str(),"Empty=%d;",&n);
       empty = n;
    }
    else if(buffer.find("Head")!=-1)
    {
       sscanf((const char*)buffer.c_str(),"Head=%d;",&n);
       head = n;
    }
    else if(buffer.find("Tail")!=-1)
    {
       sscanf((const char*)buffer.c_str(),"Tail=%d;",&n);
       tail = n;
    }
    else if(buffer.find("Wire")!=-1)
    {
       sscanf((const char*)buffer.c_str(),"Wire=%d;",&n);
       wire = n;
    }
    else if(buffer.find("Zero")!=-1)
    {
       sscanf((const char*)buffer.c_str(),"Zero=%d;",&n);
       zero = n;
    }
    else if(buffer.find("One")!=-1)
    {
       sscanf((const char*)buffer.c_str(),"One=%d;",&n);
       one = n;
    }
    check(n);
}

void Chars::removeSpaces(string str)
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
    setCha();
}

void Chars::check(int n)
{
    try{
        if(n<0 || n>255) throw -1;
    }
    catch(int a)
    {
        cerr<<"Invalid character value. Program terminated."<<endl;
        exit(1);
    }
}
