#include "poison.h"

Poison::Poison(int w, int h, QPoint p)
{
    // initialise the sweet data
    width = w;
    height = h;
    position = p;
}

// a fcuntion to return the width of a candy
int &Poison::getWidth()
{
    return width;
}

// a fucntion to return the height of a candy
int &Poison::getHeight()
{
    return height;
}

// a function to return the position of a candy
QPoint Poison::getPosition()
{
    return position;
}

// a function which returns the value of the sweet
int Poison::value()
{
    // the snake loses an inch
    return Value::Shrink;
}
