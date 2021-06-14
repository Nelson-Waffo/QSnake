#include "squarewindow.h"

SquareWindow::SquareWindow(QPoint p, int w, int h)
{
   position = p; width = w; height = h;
}

QPoint &SquareWindow::getPosition()
{
    return position;
}

int &SquareWindow::getWidth()
{
    return width;
}

int &SquareWindow::getHeight()
{
    return height;
}
