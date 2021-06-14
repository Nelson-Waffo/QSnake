#include "cabin.h"

Cabin::Cabin(int w, int h, QList<Wall *>& wa, QList<Window*>& wi)
{
    walls = wa;
    windows = wi;
    width = w; height = h;
}

// destructor for the cabin house
Cabin::~Cabin()
{
}

// a function which returns walls for the house
QList<Wall *>& Cabin::getWalls()
{
    return walls;
}

//a function which returns windows for the house
QList<Window *>& Cabin::getWindows()
{
    return windows;
}

// a function which returns width for the house
int& Cabin::getWidth()
{
    return width;
}

// a function which returns height for the house
int& Cabin::getHeight()
{
    return height;
}
