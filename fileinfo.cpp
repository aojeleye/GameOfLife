#include "fileinfo.h"

FileInfo::FileInfo()
{
    init();
}

void FileInfo::init()
{
    //Name
    name = "";
    //Rule value
    rule = 0;
    //Colors
    Acolor = new int[3];
    Dcolor = new int[3];
    Ocolor = new int[3];
    Zcolor = new int[3];
    Ecolor = new int[3];
    Hcolor = new int[3];
    Tcolor = new int[3];
    Wcolor = new int[3];
    //Cell coordinate arrays
    Ocoor = NULL;
    Acoor = NULL;
    Tcoor = NULL;
    Hcoor = NULL;
    Wcoor = NULL;
    //Length of cell coordinate arrays
    AcoordLen = 0;
    HcoordLen = 0;
    WcoordLen = 0;
    TcoordLen = 0;
    OcoordLen = 0;
    //Chars
    alive = 0;
    dead = 0;
    empty = 0;
    wire = 0;
    head = 0;
    tail = 0;
    zero = 0;
    one = 0;
    filetype = 0;
    //Terrain ranges
    txRangeHigh = 0;
    txRangeLow = 0;
    tyRangeHigh = 0;
    tyRangeLow = 0;
    //Window ranges
    wxRangeHigh = 0;
    wxRangeLow = 0;
    wyRangeHigh = 0;
    wyRangeLow = 0;
    //Boolean flag holding object for parsing file
    p = new Parse();
}

/*Loops through arguments to find
 *the first valid file name and opens
 *said file. If no valid file name found
 *then passes on stdin as the input file stream*/
/*argc - number of arguments*/
/*agv - argument strings*/
void FileInfo::openFile(int argc,const char* agv[])
{
    FILE* file;
    for(int i = 1;i<argc;i++)
    {
        file = fopen(agv[i],"r");
        if(file)
        {
            compactFile(file);
            break;
        }
    }
    if(!file)
        compactFile(stdin);
}
/*Strips the given file of all
 *comments and return characters. Writes a
 *new file omitting the above characters*/
/*file - file to be stripped/parsed*/
void FileInfo::compactFile(FILE* file)
{
    FILE* temp = fopen("temp.txt","w");
    char c = 0;
    string buffer = "";

    while(!feof(file))
    {
        c = fgetc(file);
        if(c=='#')
        {
            while(!feof(file) && c!='\n')
             c = fgetc(file);
        }
        //Handles getting the name of the game simulation
        else if(!feof(file) && c=='"')
        {
            buffer+= c;
            c = fgetc(file);
            while(!feof(file) && c!='"')
            {
               buffer+= c;
               c = fgetc(file);
            }
            buffer+= c;
        }
        else if(c=='{')
        {
           print(temp,buffer,c);
           buffer = "";
        }
        //Omits \n,\r,and ; from the char array.
        else if(c!=';' && c!='\n' && c!='\r')
            buffer+= c;
        //When we hit a ; then we've reached the end of a statement
        else if(c==';')
        {
            print(temp,buffer,c);
            buffer = "";
        }

    }
    fclose(temp);
    parse();
}
void FileInfo::print(FILE* temp,string buffer,char c)
{
    buffer+= c;
    if(buffer[0]!='\n')
        fputs(buffer.c_str(),temp);
    fprintf(temp,"\n");
    return;
}

void FileInfo::parse()
{
    string str;
    ifstream file;
    char filetype;
    file.open("temp.txt");

    getline(file,str);

    //Determines the filetype and whether file is valid
    checkFileType(str);

    while(!file.eof())
    {
        getline(file,str);

        //Checks if identifier has been found and records the respective flag in Parse p
        //Utilized later on for checking for duplicate identifiers
        //Also checks for quotation to determine if part of the name or not
        if(str.find("\n")!=-1 && str.find("\"")==-1 && str.find("Terrain")!=-1)
           p->setFoundT(true);
        else if(str.find("\n")!=-1 && str.find("\"")==-1 && str.find("Window")!=-1)
            p->setFoundW(true);
        else if(str.find("\n")!=-1 && str.find("\"")==-1 && str.find("Colors")!=-1)
            p->setFoundCol(true);
        else if(str.find("\n")!=-1 && str.find("\"")==-1 && str.find("Initial")!=-1)
            p->setFoundInit(true);
        else if(str.find("\n")!=-1 && str.find("\"")==-1 && str.find("Chars")!=-1)
            p->setFoundCh(true);

        if(str.find("Name")!=-1)
        {
            Name n(str);
            name = n.get();
        }
        else if(str.find("Rule")!=-1 && str.find("\"")==-1)
        {
            Rule r(str);
            rule = r.get();
        }
        else if(str.find("Terrain")!=-1 && str.find("\"")==-1)
        {
            Terrain *ter = new Terrain();

            while(str.find("};")==-1 && !file.eof())
            {
                getline(file,str);
                ter->removeSpaces(str);  
            }
            tyRangeHigh = ter->getYHigh();
            tyRangeLow = ter->getYLow();
            txRangeHigh = ter->getXHigh();
            txRangeLow = ter->getXLow();
        }
        else if(str.find("Chars")!=-1 && str.find("\"")==-1)
        {
            Chars *ch = new Chars();

            while(str.find("};")==-1 && !file.eof())
            {
                getline(file,str);
                ch->removeSpaces(str);
            }
            alive = ch->getAliveCh();
            dead = ch->getDeadCh();
            empty = ch->getEmptyCh();
            wire = ch->getWireCh();
            head = ch->getHeadCh();
            tail = ch->getTailCh();
            zero = ch->getZeroCh();
            one = ch->getOneCh();
        }
        else if(str.find("Colors")!=-1 && str.find("\"")==-1)
        {
            Colors *col = new Colors();

            while(str.find("};")==-1 && !file.eof())
            {
                getline(file,str);
                col->removeSpaces(str);
            }
            Acolor = col->getAliveColor();
            Dcolor = col->getDeadColor();
            Ocolor = col->getOneColor();
            Zcolor = col->getZeroColor();
            Ecolor = col->getEmptyColor();
            Hcolor = col->getHeadColor();
            Tcolor = col->getTailColor();
            Wcolor = col->getWireColor();
        }
        else if(str.find("Initial")!=-1 && str.find("\"")==-1)
        {
            Initial *in = new Initial();
            while(str.find("};")==-1 && !file.eof())
            {
                getline(file,str);
                in->removeSpaces(str);
            }
            AcoordLen = in->getACoordLen();
            HcoordLen = in->getHCoordLen();
            WcoordLen = in->getWCoordLen();
            TcoordLen = in->getTCoordLen();
            OcoordLen = in->getOCoordLen();
            Ocoor = in->getOneCoor();
            Acoor = in->getAliveCoor();
            Tcoor = in->getTailCoor();
            Hcoor = in->getHeadCoor();
            Wcoor = in->getWireCoor();

        }
        else if(str.find("Window")!=-1 && str.find("\"")==-1)
        {
            Window *win = new Window();

            while(str.find("};")==-1 && !file.eof())
            {
                getline(file,str);
                win->removeSpaces(str);
            }
            wyRangeHigh = win->getYHigh();
            wyRangeLow = win->getYLow();
            wxRangeHigh = win->getXHigh();
            wxRangeLow = win->getXLow();
        }
}
}

void FileInfo::override(int txh,int txl,int tyh,int tyl,int wxh,int wxl,int wyh,int wyl)
{
    if(wxh!=0 || wxl!=0)
    {
        wxRangeHigh = wxh;
        wxRangeLow = wxl;
    }
    if(wyh!=0 || wyl!=0)
    {
        wyRangeHigh = wyh;
        wyRangeLow = wyl;
    }
    if(txh!=0 || txl!=0)
    {
        txRangeHigh = txh;
        txRangeLow = txl;
    }
    if(tyh!=0 || tyl!=0)
    {
        tyRangeHigh = tyh;
        tyRangeLow = tyl;
    }

    /*Covers case where window ranges are not
     *specified in either the command line or file*/
    /*Takes the window ranges from file terrain if terrain and
     *window are not specified on the command line and window
     *is not specified in the file*/
    if(wxRangeHigh==0 && wxRangeLow==0)
    {
        wxRangeHigh = txRangeHigh;
        wxRangeLow = txRangeLow;
    }
    if(wyRangeHigh==0 && wyRangeLow==0)
    {
        wyRangeHigh = tyRangeHigh;
        wyRangeLow = tyRangeLow;
    }
}

/*Determines if an identifier has a duplicate in the input file.
 *Throws an error if duplicate detected*/
void FileInfo::checkIDs(string str)
{
    /*Checks to see if a quotation mark is in the string to handle
     *the case of the Name containing a keyword*/
    try{
        if(str.find("\"")!=-1 && str.find("Initial")!=-1  && p->getFoundInit())
        {
            fprintf(stderr,"Double initial\n");
            throw -1;
        }
        if(str.find("\"")!=-1 && str.find("Chars")!=-1 && p->getFoundCh())
        {
            fprintf(stderr,"Double chars\n");
            throw -1;
        }
        if(str.find("\"")!=-1 && str.find("Colors")!=-1 && p->getFoundCol())
        {
            fprintf(stderr,"Double colors\n");
            throw -1;
        }
        if(str.find("\"")!=-1 && str.find("Window")!=-1 && p->getFoundW())
        {
            fprintf(stderr,"Double window\n");
            throw -1;
        }
        if(str.find("\"")!=-1 && str.find("Terrain")!=-1 && p->getFoundT())
        {
            fprintf(stderr,"Double terrain\n");
            throw -1;
        }
    }
    catch(int a)
    {
        cerr<<"Duplicate Identifer detected. Program terminated."<<endl;
        exit(1);
    }
}

void FileInfo::checkKeyValues()
{
    /*Checks to see if key values were specified.
     *Doesn't check if window values are 0 since
     *the terrain values will over them*/
    try{
        if(rule<0 || rule>255) throw -1;
        if(txRangeHigh==0 && txRangeLow==0) throw -1;
        if(tyRangeHigh==0 && tyRangeLow==0) throw -1;
        if(txRangeLow>txRangeHigh) throw -1;
        if(tyRangeLow>tyRangeHigh) throw -1;
        if(wxRangeLow>wxRangeHigh) throw -1;
        if(wyRangeLow>wyRangeHigh) throw -1;
        if(filetype=='l')
        {
            if(Acolor == NULL) throw -1;
            if(Dcolor == NULL) throw -1;
        }
        else if(filetype=='w')
        {
            if(Wcolor == NULL) throw -1;
            if(Hcolor == NULL) throw -1;
            if(Tcolor == NULL) throw -1;
            if(Ecolor == NULL) throw -1;
        }
        else if(filetype=='e')
        {
            if(Ocolor == NULL) throw -1;
            if(Zcolor == NULL) throw -1;
        }
    }
    catch(int a)
    {
        cerr<<"Invalid keyvalues. Program terminated."<<endl;
        exit(1);
    }
}

void FileInfo::checkFileType(string str)
{
    try{
        if(str.find("Life")!=-1)
            filetype = 'l';
        else if(str.find("WireWorld")!=-1)
            filetype = 'w';
        else if(str.find("Elementary")!=-1)
            filetype = 'e';
        else
            throw -1;
    }
    catch(int a)
    {
        printf("Invalid file type. Program terminated.\n");
        exit(1);
    }
}

void FileInfo::display()
{
    if(filetype=='l')
        displayLife();
    else if(filetype=='w')
        displayWireWorld();
    else if(filetype=='e')
        displayElementary();
}

void FileInfo::displayLife()
{
    int i = 0;

    printf("Life = {\n");
    printf("Name = \"%s\"\";\n",name.c_str());
    printf("Terrain = {\n");
    printf("    Xrange = %d..%d;\n",txRangeLow,txRangeHigh);
    printf("    Yrange = %d..%d;\n};\n",tyRangeLow,tyRangeHigh);
    printf("Window = {\n");
    printf("    Xrange = %d..%d\n",wxRangeLow,wxRangeHigh);
    printf("    Yrange = %d..%d\n};\n",wyRangeLow,wyRangeHigh);
    printf("Colors = {\n");
    printf("    Alive = (%d,%d,%d)\n",Acolor[0],Acolor[1],Acolor[2]);
    printf("    Dead = (%d,%d,%d)\n};\n",Dcolor[0],Dcolor[1],Dcolor[2]);
    printf("Chars = {\n");
    printf("    Alive char: %c\n",alive);
    printf("    Dead char: %c\n};\n",dead);
    printf("Initial = {\n");
    printf("Alive = ");
    while(i<AcoordLen)
    {
        if(i+2==AcoordLen)
        {
            printf("(%d,",Acoor[i++]);
            printf("%d)",Acoor[i++]);
        }
        else
        {
            printf("(%d,",Acoor[i++]);
            printf("%d), ",Acoor[i++]);
        }
    }
    printf(";\n};\n};\n");
}

void FileInfo::displayWireWorld()
{
    int i = 0,j = 0,k = 0;

    printf("WireWorld = {\n");
    printf("Name = \"%s\"\";\n",name.c_str());
    printf("Terrain = {\n");
    printf("    Xrange = %d..%d;\n",txRangeLow,txRangeHigh);
    printf("    Yrange = %d..%d;\n};\n",tyRangeLow,tyRangeHigh);
    printf("Window = {\n");
    printf("    Xrange = %d..%d\n",wxRangeLow,wxRangeHigh);
    printf("    Yrange = %d..%d\n};\n",wyRangeLow,wyRangeHigh);
    printf("Colors = {\n");
    printf("    Wire = (%d,%d,%d)\n",Wcolor[0],Wcolor[1],Wcolor[2]);
    printf("    Head = (%d,%d,%d)\n};\n",Hcolor[0],Hcolor[1],Hcolor[2]);
    printf("    Tail = (%d,%d,%d)\n",Tcolor[0],Tcolor[1],Tcolor[2]);
    printf("    Empty = (%d,%d,%d)\n};\n",Ecolor[0],Ecolor[1],Ecolor[2]);
    printf("Chars = {\n");
    printf("    Wire char: %c\n",wire);
    printf("    Head char: %c\n};\n",head);
    printf("    Tail char: %c\n",tail);
    printf("    Empty char: %c\n};\n",empty);
    printf("Initial = {\n");
    printf("Wire = ");
    while(i<WcoordLen)
    {
        if(i+2==WcoordLen)
        {
            printf("(%d,",Wcoor[i++]);
            printf("%d)",Wcoor[i++]);
        }
        else
        {
            printf("(%d,",Wcoor[i++]);
            printf("%d), ",Wcoor[i++]);
        }
    }
    printf(";\n");
    printf("Head = ");
    while(j<HcoordLen)
    {
        if(j+2==HcoordLen)
        {
            printf("(%d,",Hcoor[j++]);
            printf("%d)",Hcoor[j++]);
        }
        else
        {
            printf("(%d,",Hcoor[j++]);
            printf("%d), ",Hcoor[j++]);
        }
    }
    printf(";\n");
    printf("Tail = ");
    while(k<TcoordLen)
    {
        if(k+2==TcoordLen)
        {
            printf("(%d,",Tcoor[k++]);
            printf("%d)",Tcoor[k++]);
        }
        else
        {
            printf("(%d,",Tcoor[k++]);
            printf("%d), ",Tcoor[k++]);
        }
    }
    printf(";\n};\n};\n");
}

void FileInfo::displayElementary()
{
    int i = 0;
    printf("Elementary = {\n");
    printf("Name = \"%s\"\";\n",name.c_str());
    printf("Rule = %d\n",rule);
    printf("Terrain = {\n");
    printf("    Xrange = %d..%d;\n",txRangeLow,txRangeHigh);
    printf("    Yrange = %d..%d;\n};\n",tyRangeLow,tyRangeHigh);
    printf("Window = {\n");
    printf("    Xrange = %d..%d\n",wxRangeLow,wxRangeHigh);
    printf("    Yrange = %d..%d\n};\n",wyRangeLow,wyRangeHigh);
    printf("Colors = {\n");
    printf("    One = (%d,%d,%d)\n",Ocolor[0],Ocolor[1],Ocolor[2]);
    printf("    Zero = (%d,%d,%d)\n};\n",Zcolor[0],Zcolor[1],Zcolor[2]);
    printf("Chars = {\n");
    printf("    One char: %c\n",one);
    printf("    Zero char: %c\n};\n",zero);
    printf("Initial = {\n");
    printf("One = ");
    while(i<OcoordLen)
    {
        if(i+2==OcoordLen)
        {
            printf("(%d,",Ocoor[i++]);
            printf("%d)",Ocoor[i++]);
        }
        else
        {
            printf("(%d,",Ocoor[i++]);
            printf("%d), ",Ocoor[i++]);
        }
    }
    printf(";\n};\n};\n");
}
