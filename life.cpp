#include <iostream>
#include <stdio.h>
#include <string>
#include "flags.h"
#include "board.h"
#include "fileinfo.h"
#include "board.h"

using namespace std;

void helpScreen();
int main(int argc, const char* agv[])
{
    Flags flag;
    FileInfo info;

    flag.parse(argc,agv);
    info.openFile(argc,agv);
    info.override(flag.getTxHigh(),flag.getTxLow(),flag.getTyHigh(),flag.getTyLow(),
                  flag.getWxHigh(),flag.getWxLow(),flag.getWyHigh(),flag.getWyLow());
    if(flag.getHelp())
    {
        helpScreen();
        return 0;
    }
    else if(flag.getFileOutput())
    {
        info.display();
        return 0;
    }

    Board b(info,flag);
    b.run();
    b.displayWindow();
    return 0;
}

// Brief printed explanation of how the program operates.
void helpScreen()
{
    fprintf(stdout,"\tReads an input file via arguments or standard input. The file contains\n"
            "values for terrain ranges,alive and dead characters plus colors and window ranges(optional)"
            "The program simulates a cellular automaton game called Game of Life where based"
            "on initial conditions cells will go through death and rebirth represented by a grid."
            "\n--Arguments--\n"
            "-f,            Outputs values in file format\n"
            "-v,            Outputs values in ASCII art fashion. -f takes precedence over this flag.\n"
            "\t\t\tIf both -f and -v omitted, outputs ASCII art representation by default\n"
            "-g,            Determines how many cycles for the cells to go through. Default is 0.\n"
            "-tx l..h       Set the x range of the terrain. overrides values in the input file.\n"
            "-ty l..h       Set the y range of the terrain. overrides values in the input file.\n"
            "-wx l..h       Set the x range of the window. tx overrides this if wx is not specified.\n"
            "-wy l..h       Set the y range of the window. ty overrides this if wy is not specified.\n"
            "\n--Errors--\n"
            "Program terminates if:\n"
            "1. Invalid key values are found (ex. 0s for all ranges,high value lower than low value)\n"
            "2. Invalid file type. Only Life, Elementary and Wire valid.\n"
            "3. If name field is empty.\n"
            "4. Missing coordinate value.\n"
            "5. Alive or Dead character set to an int value below 0 or above 255.\n"
            "6. If any color value is below 0 or above 255.\n"
            "7. If a duplicate identifier is detected in the input file.\n");
}


