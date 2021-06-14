#ifndef SQUAREWINDOW_H
#define SQUAREWINDOW_H

#include "window.h"
// a class to define square windows
class SquareWindow :public Window
{
public:
    SquareWindow(QPoint, int, int);
    QPoint& getPosition() override;
    int& getWidth()override;
    int& getHeight()override;
};

#endif // SQUAREWINDOW_H
