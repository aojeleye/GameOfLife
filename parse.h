#ifndef PARSE_H
#define PARSE_H

class Parse
{
    //True if Initial identifier found. False otherwise.
    bool foundInit;
     //True if Color identifier found. False otherwise.
    bool foundCol;
     //True if Char identifier found. False otherwise.
    bool foundCh;
     //True if Window identifier found. False otherwise.
    bool foundW;
     //True if Terrain identifier found. False otherwise.
    bool foundT;

    public:
        Parse();

        inline void setFoundInit(bool r){
            foundInit = r;
        }
        inline void setFoundCol(bool r){
            foundCol = r;
        }
        inline void setFoundW(bool r){
            foundW = r;
        }
        inline void setFoundT(bool r){
            foundT = r;
        }
        inline void setFoundCh(bool r){
            foundCh = r;
        }
        inline bool getFoundInit(){
            return foundInit;
        }
        inline bool getFoundCol(){
            return foundCol;
        }
        inline bool getFoundW(){
            return foundW;
        }
        inline bool getFoundT(){
            return foundT;
        }
        inline bool getFoundCh(){
            return foundCh;
        }
};

#endif // PARSE_H
