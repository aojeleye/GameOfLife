#include "colors.h"

Colors::Colors()
{
    Acolor = new int[3];
    Dcolor = new int[3];
    Ocolor = new int[3];
    Zcolor = new int[3];
    Ecolor = new int[3];
    Hcolor = new int[3];
    Tcolor = new int[3];
    Wcolor = new int[3];
    buffer = "";
}

void Colors::removeSpaces(string str)
{
    string temp = "";
    buffer = str;

    for(int i = 0;i<buffer.length();i++)
    {
        if(buffer[i] != ' ')
            temp+=buffer[i];
        if(buffer[i]==';')
            break;
    }
    buffer = temp;
    setColors();
}

void Colors::setColors()
{
    int fvalue= 0;
    int svalue = 0;
    int tvalue = 0;

    if(buffer.find("Alive")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Alive=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Acolor[0] = fvalue;
        Acolor[1] = svalue;
        Acolor[2] = tvalue;
    }
    else if(buffer.find("Dead")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Dead=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Dcolor[0] = fvalue;
        Dcolor[1] = svalue;
        Dcolor[2] = tvalue;
    }
    else if(buffer.find("Empty")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Empty=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Ecolor[0] = fvalue;
        Ecolor[1] = svalue;
        Ecolor[2] = tvalue;
    }
    else if(buffer.find("Head")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Head=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Hcolor[0] = fvalue;
        Hcolor[1] = svalue;
        Hcolor[2] = tvalue;
    }
    else if(buffer.find("Tail")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Tail=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Tcolor[0] = fvalue;
        Tcolor[1] = svalue;
        Tcolor[2] = tvalue;
    }
    else if(buffer.find("Wire")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Wire=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Wcolor[0] = fvalue;
        Wcolor[1] = svalue;
        Wcolor[2] = tvalue;
    }
    else if(buffer.find("Zero")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Zero=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Zcolor[0] = fvalue;
        Zcolor[1] = svalue;
        Zcolor[2] = tvalue;
    }
    else if(buffer.find("One")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"One=(%d,%d,%d)",&fvalue,&svalue,&tvalue);
        Ocolor[0] = fvalue;
        Ocolor[1] = svalue;
        Ocolor[2] = tvalue;
    }
    check(fvalue,svalue,tvalue);
}
void Colors::check(int a,int b,int c)
{
    try{

            if(a>255 || a<0) throw -1;
            if(b>255 || b<0) throw -1;
            if(c>255 || c<0) throw -1;
    }
    catch(int a)
    {
        cerr<<"Invalid color pixel value. Program terminated."<<endl;
        exit(1);
    }
}

