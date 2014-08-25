#include "boardgui.h"
#include <stdio.h>

BoardGUI::BoardGUI(QWidget *parent,FileInfo info,Flags flags)
    : QWidget(parent),fi(info),fl(flags)
{
     x = abs(fi.getWxHigh()-fi.getWxLow())+1;
     y = abs(fi.getWyHigh()-fi.getWyLow())+1;
     gen = fl.getGen();
     acolor = fi.getAliveColor();
     dcolor = fi.getDeadColor();
     zcolor = fi.getZeroColor();
     ocolor = fi.getOneColor();
     hcolor = fi.getHeadColor();
     tcolor = fi.getTailColor();
     wcolor = fi.getWireColor();
     ecolor = fi.getEmptyColor();
     filetype = fi.getFileType();
     alive = fi.getAliveCh();
     dead = fi.getDeadCh();
     zero = fi.getZeroCh();
     one = fi.getOneCh();
     head = fi.getHeadCh();
     tail = fi.getTailCh();
     wire = fi.getWireCh();
     empty = fi.getEmptyCh();
     b = new Board(fi,fl);
     b->run();
     board = b->getBoard();
     setAttribute(Qt::WA_StaticContents);
     setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
     curColor = Qt::black;
     zoom = fl.getSize();
     image = QImage(x,y, QImage::Format_ARGB32);
     image.fill(qRgba(255, 0, 0, 0));
}

void BoardGUI::process(int cycles)
{
    b->setGen(cycles);
    b->run();
    board = b->getBoard();
    repaint();
}

QSize BoardGUI::sizeHint() const
{
     QSize size = zoom * image.size();
     if (zoom >= 3)
     size += QSize(1, 1);
     return size;
}

void BoardGUI::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

void BoardGUI::setBoardImage(const QImage &newImage)
{
     if (newImage != image) {
     image = newImage.convertToFormat(QImage::Format_ARGB32);
     update();
     updateGeometry();
     }
}

void BoardGUI::setZoomFactor(int newZoom)
{
     if (newZoom < 1)
     newZoom = 1;
     if (newZoom != zoom) {
     zoom = newZoom;
     update();
     updateGeometry();
     }
}

void BoardGUI::paintEvent(QPaintEvent *event)
{
    /*The board has its origin in the lower left corner.
     *The origin for Qt is the upper left corner so we
     *start at y-1 (last row) for board to obtain the
     *correct behavior*/
     int yBound = y-1;

     QPainter painter(this);
     if (zoom >= 4) {
            painter.setPen(palette().foreground().color());
         for (int i = 0; i <= image.width(); ++i)
            painter.drawLine(zoom * i, 0,
         zoom * i, zoom * image.height());
         for (int j = 0; j <= image.height(); ++j)
            painter.drawLine(0, zoom * j,
         zoom * image.width(), zoom * j);
     }
     /*Fills rectangles left to right, top to bottom*/
     for (int i = 0; i < image.height(); ++i) {
      for (int j = 0; j < image.width(); ++j)
      {
          QRect rect = pixelRect(j, i);
          /*Default color*/
          QColor *color = new QColor(0,0,0,255);
          if(filetype == 'l')
          {
              if(board[yBound][j].get()==dead)
                  color = new QColor(dcolor[0],dcolor[1],dcolor[2],255);
              else if((board[yBound][j]).get()==alive)
                  color = new QColor(acolor[0],acolor[1],acolor[2],255);
          }
          else if(filetype == 'e')
          {
              if(board[yBound][j].get()==zero)
                  color = new QColor(zcolor[0],zcolor[1],zcolor[2],255);
              else if((board[yBound][j]).get()==one)
                  color = new QColor(ocolor[0],ocolor[1],ocolor[2],255);
          }
          else if(filetype == 'w')
          {
              if(board[yBound][j].get()==wire)
                  color = new QColor(wcolor[0],wcolor[1],wcolor[2],255);
              else if((board[yBound][j]).get()==empty)
                  color = new QColor(ecolor[0],ecolor[1],ecolor[2],255);
              else if(board[yBound][j].get()==head)
                  color = new QColor(hcolor[0],hcolor[1],hcolor[2],255);
              else if((board[yBound][j]).get()==tail)
                  color = new QColor(tcolor[0],tcolor[1],tcolor[2],255);
          }
          painter.fillRect(rect, *color);
      }
      yBound--;
  }
}
QRect BoardGUI::pixelRect(int i, int j) const
{
     if (zoom >= 3) {
     return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
     } else {
     return QRect(zoom * i, zoom * j, zoom, zoom);
     }
}

