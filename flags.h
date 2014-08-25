#ifndef FLAGS_H
#define FLAGS_H

class Flags
{
    //True if flag -f detected. False otherwise
    bool fileOutput;
    //True if flag -v detected. False otherwise
    bool visualOutput;
    //True if flag -h detected. False otherwise
    bool help;
    //Displays dialog box with various controls for life_gui program if true
    bool controls;
    //Number of generations to be cycle'd
    int gen;
    //Size of drawn rectangles
    int size;
    //Terrain high end of x range
    int txRangeHigh;
    //Terrain low end of x range
    int txRangeLow;
    //Terrain high end of y range
    int tyRangeHigh;
    //Terrain low end of y range
    int tyRangeLow;
    //Window high end of x range
    int wxRangeHigh;
    //Window low end of x range
    int wxRangeLow;
    //Window high end of y range
    int wyRangeHigh;
    //Window low end of y range
    int wyRangeLow;


    public:
        Flags();

        /*Parses the command line for valid
         *switches and sets the next argument to
         *a key value for generation and x and y
         *range for terrain and window respectively*/
        /*argc - number of arguments*/
        /*agv - contains argument strings*/
        void parse(int,const char*[]);

        /*Prints out key values from command line*/
        void display();

        inline bool getControls(){
            return controls;
        }
        inline int getGen(){
            return gen;
        }
        inline bool getHelp(){
            return help;
        }
        inline bool getFileOutput(){
            return fileOutput;
        }
        inline int getTxLow(){
            return txRangeLow;
        }
        inline int getTxHigh(){
            return txRangeHigh;
        }
        inline int getTyLow(){
            return tyRangeLow;
        }
        inline int getTyHigh(){
            return tyRangeHigh;
        }
        inline int getWxLow(){
            return wxRangeLow;
        }
        inline int getWxHigh(){
            return wxRangeHigh;
        }
        inline int getWyLow(){
            return wyRangeLow;
        }
        inline int getWyHigh(){
            return wyRangeHigh;
        }
        inline int getSize(){
            return size;
        }

    private:
        /*Checks to see if wyRange values and/or
         *wxRange values were set by the user. If not
         *then set them equal to tyRange and txRange
         *respectively*/
        void check();
};

#endif // FLAGS_H
