#ifndef BOARDGUI_H
#define BOARDGUI_H
#include "cell.h"
#include "flags.h"
#include "fileinfo.h"
#include <QtGui>
#include <QColor>
#include <QImage>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <iostream>
#include <stdlib.h>
#include "board.h"

using namespace std;

/*Disclaimer: This class is based off an example from
 *Chapter 5 including some core functions from IconEditor, in C++ GUI Programming with Qt 4
 *by Jasmin Blanchette and Mark Summerﬁeld*/
class BoardGUI : public QWidget
{
    //Width of image
    int x;
    //Height of image
    int y;
    //Zoom factor for image
    int zoom;
    //Generation value given by user
    int gen;
    //Alive cell color
    int *acolor;
    //Dead cell color
    int *dcolor;
    //Zero cell color
    int *zcolor;
    //One cell color
    int *ocolor;
    //Head cell color
    int *hcolor;
    //Tail cell color
    int *tcolor;
    //Wire cell color
    int *wcolor;
    //Empty cell color
    int *ecolor;
    //'l' for life file, 'e' for elementary, and 'w' for wireworld
    char filetype;
    //Character for alive cell
    char alive;
    //Character for dead cell
    char dead;
    //Character for zero cell
    char zero;
    //Character for one cell
    char one;
    //Character for head cell
    char head;
    //Character for tail cell
    char tail;
    //Character for wire cell
    char wire;
    //Character for empty cell
    char empty;
    //Board object which contains grid of cells
    Board *b;
    //Contains file keyvalues/words
    FileInfo fi;
    //Contains switches and respective values from command line
    Flags fl;
    //Current color
    QColor curColor;
    //Image to be drawn on for the grid
    QImage image;
    //2D array of cells to be obtained from Board class
    Cell **board;

    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage boardImage READ boardImage WRITE setBoardImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

    public:

        /*Constructor for a graphical representation of board class that holds
         *a 2D Cell array for our game simulation
         *parent - parent widget of class object
         *fi - object that contains keyvalues/words from input file
         *fl - object that contains switches and values from command line*/
        BoardGUI();
        BoardGUI(QWidget *parent,FileInfo info,Flags flags);

        inline void setBoard(Cell **b){
            board = b;
        }
        inline int getZoom(){
            return zoom;
        }

        /*Sets color of pen for drawing image*/
        void setPenColor(const QColor &newColor);

        /*Returns QColor object containing current color of pen*/
        QColor penColor() const { return curColor; }

        /*Sets zoom factor*/
        void setZoomFactor(int newZoom);

        /*Returns zoom factor*/
        int zoomFactor() const { return zoom; }

        /*Sets image for board graphic*/
        void setBoardImage(const QImage &newImage);

        /*Returns board image*/
        QImage boardImage() const { return image; }

        /*Size hint for displaying purposes*/
        QSize sizeHint() const;

        /*Runs the board aging process up to
         *cycles and grabs the final stage.
         *Repaints it onto the displayed window*/
        void process(int cycles);


        private:
            QRect pixelRect(int i, int j) const;

            /*Draws the lines of the grid with respect
             *to the zoom factor then colors the
             *created cells via determing the cell type
             *from traversing the board*/
            void paintEvent(QPaintEvent *event);

};

#endif // BOARDGUI_H
