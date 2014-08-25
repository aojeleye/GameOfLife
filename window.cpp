#include "window.h"

Window::Window()
{
    wxRangeHigh = 0;
    wxRangeLow = 0;
    wyRangeHigh = 0;
    wyRangeLow = 0;
    buffer = "";
}

void Window::setWin()
{
    int low = 0;
    int high = 0;
    if(buffer.find("Xrange")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Xrange=%d..%d",&low,&high);
        wxRangeHigh = high;
        wxRangeLow = low;
    }
     else if(buffer.find("Yrange")!=-1)
    {
        sscanf((const char*)buffer.c_str(),"Yrange=%d..%d",&low,&high);
        wyRangeHigh = high;
        wyRangeLow = low;
    }
}

void Window::removeSpaces(string str)
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
    setWin();
}

