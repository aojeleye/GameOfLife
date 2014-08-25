#include "initial.h"

Initial::Initial()
{
    one = NULL;
    alive = NULL;
    tail = NULL;
    head = NULL;
    wire = NULL;
    buffer = "";
    AcoordLen = 0;
    HcoordLen = 0;
    WcoordLen = 0;
    TcoordLen = 0;
    OcoordLen = 0;
}

void Initial::removeSpaces(string str)
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
    if(buffer.find("};")!=-1)
        return;
    setCoordString();
    return;
}

int Initial::numberOfCoords()
{
    int numOfCoords = 0;
    for(int i = 0;i<buffer.length();i++)
        if(buffer[i]=='(')
            numOfCoords++;
    return numOfCoords;
}

int Initial::startPoint()
{
    for(int i = 0;i<buffer.length();i++)
        if(buffer[i]=='(')
            return i;
    return 0;
}

void Initial::setCoordString()
{
    int ylen = numberOfCoords();
    string *coordList = new string[ylen];
    int i = startPoint();
    int j = 0;
    string str = "";

    /*List of strings. Each string is a coordinate
     *pair.*/
    while(j<ylen)
    {
        while(i<buffer.length() && buffer[i]!=')')
            str+=buffer[i++];
        //Grabs )
        if(i<buffer.length())
             str+=buffer[i++];

        //Skips comma inbetween ) (
        i++;
        coordList[j++] = str;
        str = "";
    }
    setCoord(coordList,ylen);
}

void Initial::setCoord(string *arr,int arrLen)
{
    //arrLen*2 = number of coordinate pairs * 2 = number of integers to store
    int *nums = new int[arrLen*2];
    int x = 0,y=0,j=0,coordLen=0;

    /*Translates the coordinate pairs into
     *a list of ints*/
    for(int i = 0;i<arrLen;i++)
    {
        coordLen+=sscanf((const char*)arr[i].c_str(),"(%d,%d)",&x,&y);
        nums[j++] = x;
        nums[j++] = y;
    }
    if(buffer.find("Alive")!=-1)
    {
        alive = nums;
        AcoordLen = coordLen;
    }
    else if(buffer.find("Head")!=-1)
    {
        head = nums;
        HcoordLen = coordLen;
    }
    else if(buffer.find("Tail")!=-1)
    {
        tail = nums;
        TcoordLen = coordLen;
    }
    else if(buffer.find("Wire")!=-1)
    {
        wire = nums;
        WcoordLen = coordLen;
    }
    else if(buffer.find("One")!=-1)
    {
        one = nums;
        OcoordLen = coordLen;
    }
    check(arr,arrLen);
}

void Initial::check(string *arr,int arrLen)
{
    try{
        //if(coordLen%2!=0) throw -1;

        //Checks for missing x or y value within a coordinate ()s
        for(int i = 0;i<arrLen;i++)
        {
            for(int j = 0;j<arr[i].length();j++)
            {
                if(j<(arr[i].length()-1) && arr[i][j] == ',' && arr[i][j+1] == ')')
                    throw -1;
                else if(j<(arr[i].length()-1) && arr[i][j] == '(' && arr[i][j+1] == ',')
                    throw -1;
                if(arr[i].find(",")==-1)
                    throw -1;
            }
        }
    }
    catch(int a)
    {
        cerr<<"Invalid coordinate pair detected. Program terminated."<<endl;
        exit(1);
    }
}
