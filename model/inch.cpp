#include "inch.h"

Inch::Inch(int w, int h, QPoint p)
{
    width = w; height = h; position = p;
}

int &Inch::getWidth()
{
    return width;
}

int &Inch::getHeight()
{
    return height;
}

QPoint &Inch::getPosition()
{
    return position;
}
