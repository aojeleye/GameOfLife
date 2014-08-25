#include "board.h"


Board::Board()
{

}

Board::Board(FileInfo fi,Flags flag)
{
    init(fi,flag);
}

void Board::init(FileInfo fi,Flags fl)
{
     filetype = fi.getFileType();
     rule = fi.getRule();
     ruleArrLen = 0;
     txRangeHigh = fi.getTxHigh();
     txRangeLow = fi.getTxLow();
     tyRangeHigh = fi.getTyHigh();
     tyRangeLow = fi.getTyLow();
     wxRangeHigh = fi.getWxHigh();
     wxRangeLow = fi.getWxLow();
     wyRangeHigh = fi.getWyHigh();
     wyRangeLow = fi.getWyLow();
     gen = fl.getGen();
     alive = fi.getAliveCh();
     dead = fi.getDeadCh();
     empty = fi.getEmptyCh();
     wire = fi.getWireCh();
     head = fi.getHeadCh();
     tail = fi.getTailCh();
     zero = fi.getZeroCh();
     one = fi.getOneCh();
     Acolor = fi.getAliveColor();
     Dcolor = fi.getDeadColor();
     Ocolor = fi.getOneColor();
     Zcolor = fi.getZeroColor();
     Ecolor = fi.getEmptyColor();
     Hcolor = fi.getHeadColor();
     Tcolor = fi.getTailColor();
     Wcolor = fi.getWireColor();
     Ocoor = fi.getOneCoor();
     Acoor = fi.getAliveCoor();
     Tcoor = fi.getTailCoor();
     Hcoor = fi.getHeadCoor();
     Wcoor = fi.getWireCoor();
     AcoordLen = fi.getACoordLen();
     HcoordLen = fi.getHCoordLen();
     WcoordLen = fi.getWCoordLen();
     TcoordLen = fi.getTCoordLen();
     OcoordLen = fi.getOCoordLen();
     coorLen = 0;
     numSetCells = 0;
     numTailCells = 0;
     numHeadCells = 0;
     txRange = abs(txRangeHigh-txRangeLow) + 1;
     tyRange = abs(tyRangeHigh-tyRangeLow) + 1;
     wxRange = abs(wxRangeHigh-wxRangeLow) + 1;
     wyRange = abs(wyRangeHigh-wyRangeLow) + 1;
     grid = new Cell*[tyRange];
     window = new Cell*[wyRange];
     winCoor = NULL;
     winHCoor = NULL;
     winTCoor = NULL;
     terCoor = NULL;
     terHCoor = NULL;
     terTCoor = NULL;
     ruleArr = NULL;

     if(filetype=='e')
         setRules();
    for(int y = 0;y<tyRange;y++)
         grid[y] = new Cell[txRange];
    for(int y = 0;y<wyRange;y++)
        window[y] = new Cell[wxRange];
    normalizeTerrain();
}

void Board::run()
{
    numSetCells = 0;
    numHeadCells = 0;
    numTailCells = 0;
    setGrid();
    while(gen-->0)
    {
        processCells();
        age();
    }
    findSetCellCoor();
    denormalize();
    normalizeWindow();
    setWindow();
}

void Board::displayTerrain()
{
     for(int y = tyRange-1;y>=0;y--)
    {
        for(int x = 0;x<txRange;x++)
        {
            (grid[y][x]).display();
        }
        printf("\n");
    }
}

void Board::displayWindow()
{
     for(int y = wyRange-1;y>=0;y--)
    {
        for(int x = 0;x<wxRange;x++)
        {
            (window[y][x]).display();
        }
        printf("\n");
    }
}

void Board::setRules()
{
    int j = 0;
    int setBit = 0;

    for(int i = 1;i<128;i*=2)
    {
       if(rule & i)
          ruleArrLen++;
    }
    ruleArr = new int[ruleArrLen];

    for(int i = 1;i<128;i*=2)
    {
       if((rule & i) && j<ruleArrLen)
           ruleArr[j++] = setBit;
       setBit++;
    }
}

void Board::setGrid()
{
    for(int y = tyRange-1;y>=0;y--)
        for(int x = 0;x<txRange;x++)
           (grid[y][x]).set(checkTerCoords(y,x));
}

void Board::setWindow()
{
    /*Checks to see if terrain range is within the window*/
    for(int y = wyRange-1;y>=0;y--)
   {
       for(int x = 0;x<wxRange;x++)
           (window[y][x]).set(checkWinCoords(y,x));
   }
}

void Board::findSetCellCoor()
{
    winCoor = new int[numSetCells*2];
    winHCoor = new int[numHeadCells*2];
    winTCoor = new int[numTailCells*2];
    int i = 0,j=0,k=0;

    for(int y = tyRange-1;y>=0;y--)
        for(int x = 0;x<txRange;x++)
        {
            if(filetype == 'l' && i<(numSetCells*2) && grid[y][x].get()==alive)
            {
                winCoor[i++] = x;
                winCoor[i++] = y;
            }
            if(filetype == 'w')
            {
                if(i<(numSetCells*2) && grid[y][x].get()==wire)
                {
                    winCoor[i++] = x;
                    winCoor[i++] = y;
                }
                if(j<(numHeadCells*2) && grid[y][x].get()==head)
                {
                    winHCoor[j++] = x;
                    winHCoor[j++] = y;
                }
                if(k<(numTailCells*2) && grid[y][x].get()==tail)
                {
                    winTCoor[k++] = x;
                    winTCoor[k++] = y;
                }
            }
            if(filetype == 'e' && i<(numSetCells*2) && grid[y][x].get()==one)
            {
                winCoor[i++] = x;
                winCoor[i++] = y;
            }
        }
}

void Board::denormalize()
{
    int i = 0,j=0,k=0,x,y;

    /*Uses the coordinates located in int array winCoor
     *which contain the location of the current alive cells
     *for this generation with respect to terrain ranges*/
    while(i<(numSetCells*2))
    {
        x = i++;
        y = i++;
        if(txRangeLow<0)
            winCoor[x] = winCoor[x] - abs(txRangeLow);
        else if(txRangeLow>0)
            winCoor[x] = winCoor[x] + txRangeLow;
        if(tyRangeLow<0)
            winCoor[y] = winCoor[y] - abs(tyRangeLow);
        else if(tyRangeLow>0)
            winCoor[y] = winCoor[y] + tyRangeLow;
    }
    if(filetype=='w')
    {
        while(j<(numTailCells*2))
        {
            x = j++;
            y = j++;
            if(txRangeLow<0)
                winTCoor[x] = winCoor[x] - abs(txRangeLow);
            else if(txRangeLow>0)
                winTCoor[x] = winCoor[x] + txRangeLow;
            if(tyRangeLow<0)
                winTCoor[y] = winCoor[y] - abs(tyRangeLow);
            else if(tyRangeLow>0)
                winTCoor[y] = winCoor[y] + tyRangeLow;
        }
        while(k<(numHeadCells*2))
        {
            x = k++;
            y = k++;
            if(txRangeLow<0)
                winHCoor[x] = winCoor[x] - abs(txRangeLow);
            else if(txRangeLow>0)
                winHCoor[x] = winCoor[x] + txRangeLow;
            if(tyRangeLow<0)
                winHCoor[y] = winCoor[y] - abs(tyRangeLow);
            else if(tyRangeLow>0)
                winHCoor[y] = winCoor[y] + tyRangeLow;
        }
    }
}


void Board::normalizeWindow()
{
    int i = 0,j=0,k=0,x,y;

    //numSetCells*2 = length of coordinate array for current alive cells
    while(i<(numSetCells*2))
    {
        //i increments broken into separate variables
        //to prevent bound errors
        x = i++;
        y = i++;

        //Normalizing the coordinates with respect to the
        //window ranges via checking the low range for both x and y
        if(wxRangeLow<0)
            winCoor[x] += abs(wxRangeLow);
        else if(wxRangeLow>0)
            winCoor[x] -= wxRangeLow;
        if(wyRangeLow<0)
            winCoor[y] += abs(wyRangeLow);
        else if(wyRangeLow>0)
            winCoor[y] -= wyRangeLow;
    }
    if(filetype=='w')
    {
        //numTailCells*2 = length of coordinate array for current tail cells
        while(j<(numTailCells*2))
        {
            //j increments broken into separate variables
            //to prevent bound errors
            x = j++;
            y = j++;

            //Normalizing the coordinates with respect to the
            //window ranges via checking the low range for both x and y
            if(wxRangeLow<0)
                winTCoor[x] += abs(wxRangeLow);
            else if(wxRangeLow>0)
                winTCoor[x] -= wxRangeLow;
            if(wyRangeLow<0)
                winTCoor[y] += abs(tyRangeLow);
            else if(wyRangeLow>0)
                winTCoor[y] -= tyRangeLow;
        }

        //numHeadCells*2 = length of coordinate array for current head cells
        while(k<(numHeadCells*2))
        {
            //k increments broken into separate variables
            //to prevent bound errors
            x = k++;
            y = k++;

            //Normalizing the coordinates with respect to the
            //window ranges via checking the low range for both x and y
            if(wxRangeLow<0)
                winHCoor[x] += abs(wxRangeLow);
            else if(wxRangeLow>0)
                winHCoor[x] -= wxRangeLow;
            if(wyRangeLow<0)
                winHCoor[y] += abs(tyRangeLow);
            else if(wyRangeLow>0)
                winHCoor[y] -= tyRangeLow;
        }
    }
}

void Board::normalizeTerrain()
{
    int i = 0,x,y;



    //Designates which array of coordinates to use depending
    //on the file type
    if(filetype=='l')
    {
        terCoor = Acoor;
        coorLen = AcoordLen;
    }
    else if(filetype=='w')
    {
        terCoor = Wcoor;
        coorLen = WcoordLen;
        terHCoor = Hcoor;
        terTCoor = Tcoor;
    }
    else if(filetype == 'e')
    {
        terCoor = Ocoor;
        coorLen = OcoordLen;
    }

    while(i<coorLen)
    {
        //i increments broken into separate variables
        //to prevent bound errors
        x = i++;
        y = i++;

        //Normalizing the coordinates (sets origin to lower left corner) with respect to the
        //terrain ranges via checking the low range for both x and y
        if(txRangeLow<0)
            terCoor[x] = terCoor[x] + abs(txRangeLow);
        else if(txRangeLow>0)
            terCoor[x] = terCoor[x] - txRangeLow;
        else
            terCoor[x] = terCoor[x];
        if(tyRangeLow<0)
            terCoor[y] = terCoor[y] + abs(tyRangeLow);
        else if(tyRangeLow>0)
            terCoor[y] = terCoor[y] - tyRangeLow;
        else
            terCoor[y] = terCoor[y];
    }

    if(filetype=='w')
    {
        i = 0;
        while(i<HcoordLen)
        {
            x = i++;
            y = i++;
            //Normalizes for head cells for wireworld file
            if(txRangeLow<0 && x<HcoordLen)
                terHCoor[x] = terHCoor[x] + abs(txRangeLow);
            else if(txRangeLow>0 && x<HcoordLen)
                terHCoor[x] = terHCoor[x] - txRangeLow;
            if(tyRangeLow<0 && y<HcoordLen)
                terHCoor[y] = terHCoor[y] + abs(tyRangeLow);
            else if(tyRangeLow>0 && y<HcoordLen)
                terHCoor[y] = terHCoor[y] - tyRangeLow;
        }
        i = 0;
        while(i<TcoordLen)
        {
            x = i++;
            y = i++;
            //Normalizes for tail cells for wireworld file
            if(txRangeLow<0 && x<TcoordLen)
                terTCoor[x] = terTCoor[x] + abs(txRangeLow);
            else if(txRangeLow>0 && x<TcoordLen)
                terTCoor[x] = terTCoor[x] - txRangeLow;
            if(tyRangeLow<0 && y<TcoordLen)
                terTCoor[y] = terTCoor[y] + abs(tyRangeLow);
            else if(tyRangeLow>0 && y<TcoordLen)
                terTCoor[y] = terTCoor[y] - tyRangeLow;
        }
    }
}

char Board::checkTerCoords(int y,int x)
{
    int i = 0;
    int s,t;
    char ch = 0;

    //Defaults to default cell type
    if(filetype=='l')
        ch = dead;
    else if(filetype=='e')
        ch = zero;
    else if(filetype=='w')
        ch = empty;

     //Checks for valid coordinates in terrain
    while(i<coorLen)
    {
        //i increments broken into separate variables
        //to prevent bound errors
        s = i++;
        t = i++;
        if(filetype == 'l')
        {
            if(x==terCoor[s] && y==terCoor[t])
            {
                ch = alive;
                numSetCells++;
                break;
            }
            else
                ch = dead;
        }
        if(filetype == 'w' && x==terCoor[s] && y==terCoor[t])
        {
            ch = wire;
            numSetCells++;
            break;
        }
        if(filetype == 'e')
        {
            if(x==terCoor[s] && y==terCoor[t])
            {
                ch = one;
                numSetCells++;
                break;
            }
            else
                ch = zero;
        }
    }
    if(filetype == 'w')
    {
        i = 0;
        while(i<HcoordLen)
        {
            s = i++;
            t = i++;
            if(x==terHCoor[s] && y==terHCoor[t])
            {
                ch = head;
                numHeadCells++;
                break;
            }
        }
        i = 0;
        while(i<TcoordLen)
        {
            s = i++;
            t = i++;
            if(x==terTCoor[s] && y==terTCoor[t])
            {
                ch = tail;
                numTailCells++;
                break;
            }
            else if(ch != head && ch != wire)
                ch = empty;
        }
    }
    return ch;
}

char Board::checkWinCoords(int y,int x)
{
    int i = 0;
    int s,t;
    char ch = 0;

    //Defaults to default cell type
    if(filetype=='l')
        ch = dead;
    else if(filetype=='e')
        ch = zero;
    else if(filetype=='w')
        ch = empty;

    //Checks for valid coordinates in window
    //and what their respective cell type is.
    //Stops and returns(cell type) when a non-default cell has been found
    while(i<(numSetCells*2))
    {
        //i increments broken into separate variables
        //to prevent bound errors
        s = i++;
        t = i++;
        if(filetype == 'l')
        {
            if(x==winCoor[s] && y==winCoor[t])
            {
                ch = alive;
                break;
            }
            else
                ch = dead;
        }
        if(filetype == 'e')
        {
            if(x==winCoor[s] && y==winCoor[t])
            {
                ch = one;
                break;
            }
            else
                ch = zero;
        }
        if(filetype == 'w' && x==winCoor[s] && y==winCoor[t])
        {
            ch = wire;
            break;
        }
    }
    if(filetype=='w')
    {
        i = 0;
        while(i<(numTailCells*2))
        {
            s = i++;
            t = i++;
            if(x==winTCoor[s] && y==winTCoor[t])
            {
                ch = tail;
                break;
            }
        }
        i = 0;
        while(i<(numHeadCells*2))
        {
            s = i++;
            t = i++;
            if(x==winHCoor[s] && y==winHCoor[t])
            {
                ch = head;
                break;
            }
            else if(ch != head && ch != wire)
                ch = empty;
        }
    }
    return ch;
}

void Board::processCells()
{
     for(int y = tyRange-1;y>=0;y--)
        for(int x = 0;x<txRange;x++)
        {
            if(filetype=='l')
            {
                if((grid[y][x]).get()==alive)
                    aliveHandle(y,x);
                else
                    deadHandle(y,x);
            }
            else if(filetype == 'w')
                wwHandle(y,x);
            else if(filetype == 'e')
                elemHandle(y,x);
        }
}
void Board::age()
{
    for(int y = tyRange-1;y>=0;y--)
       for(int x = 0;x<txRange;x++)
       {
           (grid[y][x]).updateCell();
       }
}

void Board::elemHandle(int y,int x)
{
    int roof = 0;

    if((grid[y][x]).get()==one)
    {
        (grid[y][x]).queue(one);
        return;
    }
    if(x+1<txRange && y+1<tyRange && (grid[y+1][x+1]).get()==one)
        roof|=1;
    if(y+1<tyRange && (grid[y+1][x]).get()==one)
        roof|=2;
    if(x-1>=0 && y+1<tyRange && (grid[y+1][x-1]).get()==one)
        roof|=4;
    for(int i = 0;i<ruleArrLen;i++)
    {
        if(roof==ruleArr[i])
        {
            (grid[y][x]).queue(one);
            numSetCells++;
            return;
        }
    }
    (grid[y][x]).queue(zero);
    return;
}

void Board::wwHandle(int y,int x)
{
    int headCount = 0;

    /*Checks surrounding cells for current state*/
    if(x-1>=0 && grid[y][x-1].get()==head)
        headCount++;
    if(x+1<txRange && (grid[y][x+1]).get()==head)
        headCount++;
    if(y+1<tyRange && (grid[y+1][x]).get()==head)
        headCount++;
    if(y-1>=0 && (grid[y-1][x]).get()==head)
        headCount++;
    if(x+1<txRange && y+1<tyRange && (grid[y+1][x+1]).get()==head)
        headCount++;
    if(x+1<txRange && y-1>0 && (grid[y-1][x+1]).get()==head)
        headCount++;
    if(x-1>=0 && y-1>0 && (grid[y-1][x-1]).get()==head)
        headCount++;
    if(x-1>=0 && y+1<tyRange && (grid[y+1][x-1]).get()==head)
        headCount++;

    if((grid[y][x]).get()==empty)
        (grid[y][x]).queue(empty);
    else if((grid[y][x]).get()==head)
        (grid[y][x]).queue(tail);
    else if((grid[y][x]).get()==tail)
        (grid[y][x]).queue(wire);
    else if((grid[y][x]).get()==wire)
    {
        if(headCount==2 || headCount==1)
            (grid[y][x]).queue(head);
        else
            (grid[y][x]).queue(wire);
    }
}

void Board::aliveHandle(int y,int x)
{
    int survive = 0;

    /*Checks surrounding cells for current state*/
    if(x-1>=0 && grid[y][x-1].get()==alive)
        survive++;
    if(x+1<txRange && (grid[y][x+1]).get()==alive)
        survive++;
    if(y+1<tyRange && (grid[y+1][x]).get()==alive)
        survive++;
    if(y-1>=0 && (grid[y-1][x]).get()==alive)
        survive++;
    if(x+1<txRange && y+1<tyRange && (grid[y+1][x+1]).get()==alive)
        survive++;
    if(x+1<txRange && y-1>0 && (grid[y-1][x+1]).get()==alive)
        survive++;
    if(x-1>=0 && y-1>0 && (grid[y-1][x-1]).get()==alive)
        survive++;
    if(x-1>=0 && y+1<tyRange && (grid[y+1][x-1]).get()==alive)
        survive++;

    /*If less than 2 or more than 3 cell
     *neighbors are alive, then this current
     *cell will die next cycle*/
    if(survive<2 || survive>3)
    {
        (grid[y][x]).queue(dead);
        numSetCells--;
    }
    else
        (grid[y][x]).queue(alive);
}

void Board::deadHandle(int y,int x)
{
    int survive = 0;

    /*Checks surrounding cells for current state*/
    if(x-1>=0 && grid[y][x-1].get()==alive)
        survive++;
    if(x+1<txRange && (grid[y][x+1]).get()==alive)
        survive++;
    if(y+1<tyRange && (grid[y+1][x]).get()==alive)
        survive++;
    if(y-1>=0 && (grid[y-1][x]).get()==alive)
        survive++;
    if(x+1<txRange && y+1<tyRange && (grid[y+1][x+1]).get()==alive)
        survive++;
    if(x+1<txRange && y-1>0 && (grid[y-1][x+1]).get()==alive)
        survive++;
    if(x-1>=0 && y-1>0 && (grid[y-1][x-1]).get()==alive)
        survive++;
    if(x-1>=0 && y+1<tyRange && (grid[y+1][x-1]).get()==alive)
        survive++;

    /*There must be exactly 3 alive
     *cell neighbors in order for this cell
     *to be alive next cycle*/
    if(survive==3)
    {
        (grid[y][x]).queue(alive);
        numSetCells++;
    }
    else
        (grid[y][x]).queue(dead);
}


