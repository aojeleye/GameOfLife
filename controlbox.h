#ifndef CONTROLBOX_H
#define CONTROLBOX_H
#include "boardgui.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QWidget>
#include <QSlider>
#include <QScrollArea>
#include <QTimer>
#include <stdio.h>

class ControlBox : public QDialog
{
    Q_OBJECT
    //Tracks the current generation being displayed
    int currentGen;
    //Delay value for self-automated simulating. In milliseconds
    int delay;
    //Contains keyvalues/words
    FileInfo info;
    //Contains switches and respective values from command line
    Flags flags;
    //Used to simulate animation
    QTimer *timer;
    //Vertical layout of Qwidgets
    QVBoxLayout *verLay;
    //Horizontal layout of Qwidgets
    QHBoxLayout *horLay;
    //Quit button to exit displayed window
    QPushButton *quitB;
    //Calculate button that processes selected generation and displays
    QPushButton *calculateB;
    //Advance button that advances generation by one
    QPushButton *advanceB;
    //Simulate button that simulates aging animation
    QPushButton *simulateB;
    //Restart button that resets generation to 0
    QPushButton *restartB;
    //Pause button. Pauses animation
    QPushButton *pauseB;
    //Allows a generation to be selected
    QSpinBox *genSB;
    //Displays and changes current grid size
    QSpinBox *gridSizeSB;
    //Displays current generation
    QSpinBox *displayGenSB;
    //Displays and changes delay for animation
    QSpinBox *delaySB;
    //Attaches scroll bars to displayed window
    QScrollArea *scrollArea;
    //Contains graphic representation of board class which contains grid
    BoardGUI *bg;

    private slots:
        /*Calls process for BoardGUI class for the current generation.
         *Displays it on window*/
        void process();
        /*Advances the current generation by one*/
        void advanceGen();
        /*Changes size of grid. Repaints grid to display window*/
        void changeGrid(int a);
        /*Mains the current generation display so user cannont change it*/
        void syncGen();
        /*Changes current generation to value of selected generation.
         *Processes it and displays new grid to window*/
        void calculate();
        /*Sets the delay for animation*/
        void setDelay();
        /*Starts the timer to allow a constant animation flow*/
        void simulate();
        /*Simulates animation by processing current generation, increasing
         *the value by one then displaying it*/
        void cycle();
        /*Stops timer*/
        void pause();
        /*Resets current generation to 0*/
        void reset();

    public:
        /*Constructs our dialog box which has various
         *controls to manipulate the display
         *parent - parent of this class object
         *scra - attaches scroll bars also allows us to completely close window
         *bdgui - contains grid*/
        ControlBox(QWidget *parent,QScrollArea *scra,BoardGUI *bdgui);
};

#endif // CONTROLBOX_H
