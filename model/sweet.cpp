#include "sweet.h"

Sweet::Sweet(int w, int h, QPoint p)
{
    // initialise the sweet data
    width = w;
    height = h;
    position = p;
}

// a fcuntion to return the width of a candy
int &Sweet::getWidth()
{
    return width;
}

// a fucntion to return the height of a candy
int &Sweet::getHeight()
{
    return height;
}

// a function to return the position of a candy
QPoint Sweet::getPosition()
{
    return position;
}

// a function which returns the value of the sweet
int Sweet::value()
{
    return Value::Grow;
}
