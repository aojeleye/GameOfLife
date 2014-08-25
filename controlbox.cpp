#include "controlbox.h"

ControlBox::ControlBox(QWidget *parent,QScrollArea *scrollArea,BoardGUI *boardgui)
    :QDialog(parent),scrollArea(scrollArea),bg(boardgui)
{
    currentGen = 0;
    delay = 0;
    QHBoxLayout *firstRow = new QHBoxLayout();
    QHBoxLayout *secondRow = new QHBoxLayout();
    QHBoxLayout *thirdRow = new QHBoxLayout();
    QHBoxLayout *fourthRow = new QHBoxLayout();
    QHBoxLayout *fifthRow = new QHBoxLayout();
    QHBoxLayout *sixthRow = new QHBoxLayout();
    QVBoxLayout *column = new QVBoxLayout();
    QLabel *genL = new QLabel("Select Generation");
    QLabel *currentGenL = new QLabel("Current Generation");
    QLabel *gridSizeL = new QLabel("Adjust Grid Size");
    QLabel *delayL = new QLabel("Delay");
    QFont font("Arial",12,QFont::Bold);
    timer =  new QTimer(this);
    quitB = new QPushButton("Quit");
    calculateB = new QPushButton("Calculate\nSelected Gen.");
    advanceB = new QPushButton("Advance");
    restartB = new QPushButton("Reset");
    simulateB = new QPushButton("Simulate");
    pauseB = new QPushButton("Pause");
    genSB = new QSpinBox();
    gridSizeSB = new QSpinBox();
    displayGenSB = new QSpinBox();
    delaySB = new QSpinBox();

    gridSizeSB->setValue(bg->getZoom());
    displayGenSB->setValue(currentGen);
    delaySB->setValue(0);

    //Connects widget signals to respective slots
    connect(timer,SIGNAL(timeout()),this,SLOT(cycle()));
    connect(timer,SIGNAL(timeout()),this,SLOT(syncGen()));
    connect(displayGenSB, SIGNAL(valueChanged(int)),this, SLOT(syncGen()));
    connect(calculateB, SIGNAL(clicked()),this, SLOT(calculate()));
    connect(calculateB, SIGNAL(clicked()),this, SLOT(syncGen()));
    connect(quitB, SIGNAL(clicked()),parent, SLOT(close()));
    connect(quitB, SIGNAL(clicked()),scrollArea, SLOT(close()));
    connect(genSB, SIGNAL(valueChanged(int)),genSB, SLOT(setValue(int)));
    connect(advanceB,SIGNAL(clicked()),this,SLOT(advanceGen()));
    connect(advanceB,SIGNAL(clicked()),this,SLOT(process()));
    connect(gridSizeSB,SIGNAL(valueChanged(int)),this,SLOT(changeGrid(int)));
    connect(delaySB, SIGNAL(valueChanged(int)),this, SLOT(setDelay()));
    connect(simulateB, SIGNAL(clicked()),this, SLOT(simulate()));
    connect(pauseB, SIGNAL(clicked()),this, SLOT(pause()));
    connect(restartB, SIGNAL(clicked()),this, SLOT(reset()));
    connect(restartB, SIGNAL(clicked()),this, SLOT(syncGen()));

    //Sets text style
    genL->setFont(font);
    currentGenL->setFont(font);
    gridSizeL->setFont(font);
    delayL->setFont(font);

    //Initializes ranges and sets sizes of widgets
    gridSizeSB->setRange(1,35);
    gridSizeSB->setMinimumHeight(30);
    quitB->setMinimumHeight(40);
    quitB->setMinimumWidth(20);
    genSB->setRange(0,1000);
    genSB->setMinimumHeight(30);
    genSB->setMinimumWidth(20);
    calculateB->setMinimumHeight(40);
    calculateB->setMinimumWidth(20);
    advanceB->setMinimumHeight(40);
    advanceB->setMinimumWidth(20);
    displayGenSB->setRange(0,1000000);
    displayGenSB->setMinimumHeight(30);
    displayGenSB->setMinimumWidth(20);
    simulateB->setMinimumHeight(40);
    simulateB->setMinimumWidth(20);
    restartB->setMinimumHeight(40);
    restartB->setMinimumWidth(20);
    pauseB->setMinimumHeight(40);
    pauseB->setMinimumWidth(20);
    delaySB->setRange(0,100);
    delaySB->setMinimumHeight(30);
    delaySB->setMinimumWidth(20);

    //Adds widgets to layout then sets layout to class
    firstRow->addWidget(currentGenL);
    firstRow->addWidget(displayGenSB);
    secondRow->addWidget(genL);
    secondRow->addWidget(genSB);
    thirdRow->addWidget(delayL);
    thirdRow->addWidget(delaySB);
    fourthRow->addWidget(gridSizeL);
    fourthRow->addWidget(gridSizeSB);
    fifthRow->addWidget(calculateB);
    fifthRow->addWidget(quitB);
    fifthRow->addWidget(advanceB);
    sixthRow->addWidget(restartB);
    sixthRow->addWidget(simulateB);
    sixthRow->addWidget(pauseB);
    column->addLayout(firstRow);
    column->addLayout(secondRow);
    column->addLayout(thirdRow);
    column->addLayout(fourthRow);
    column->addLayout(fifthRow);
    column->addLayout(sixthRow);
    setLayout(column);
}



void ControlBox::process()
{  
    bg->process(currentGen);
}

void ControlBox::calculate()
{
    currentGen = genSB->value();
    bg->process(genSB->value());
}

void ControlBox::advanceGen()
{
    currentGen++;
    displayGenSB->setValue(currentGen);
}
void ControlBox::changeGrid(int a)
{
    bg->setZoomFactor(a);
    bg->process(currentGen);
}

void ControlBox::syncGen()
{
    displayGenSB->setValue(currentGen);
}

void ControlBox::setDelay()
{
    delay = delaySB->value();
}

void ControlBox::simulate()
{
    timer->start(delay*1000);
}

void ControlBox::cycle()
{
    bg->process(currentGen++);
}

void ControlBox::reset()
{
    currentGen = 0;
    bg->process(currentGen);
}

void ControlBox::pause()
{
    timer->stop();
}
