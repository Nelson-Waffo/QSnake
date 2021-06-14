#ifndef CANDY_H
#define CANDY_H

#include <QPoint>
#include "enums/value.h"

// a class to represent the candies in the game
class Candy{
public:
    // basic functions for a candy
    virtual int& getWidth() = 0;
    virtual int& getHeight() = 0;
    virtual QPoint getPosition() = 0;
    // a function which returns the value of a candy
    virtual int value() = 0;
    virtual ~Candy(){}
protected:
    int width; int height;
    QPoint position;
};

#endif // CANDY_H
