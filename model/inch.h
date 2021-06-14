#ifndef INCH_H
#define INCH_H

#include "part.h"

// a class which represents an inch of the snake
class Inch : public Part
{
public:
    Inch(int w, int h, QPoint p);
    int& getWidth()override;
    int& getHeight() override;
    QPoint& getPosition() override;
};

#endif // INCH_H
