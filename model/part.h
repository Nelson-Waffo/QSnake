#ifndef PART_H
#define PART_H

#include <QPoint>

// a class which represents a part of the snake
class Part{
public:
    virtual int& getWidth() = 0;
    virtual int& getHeight() = 0;
    virtual QPoint& getPosition() = 0;
    virtual ~Part(){}
protected:
    QPoint position;
    int width; int height;
};

#endif // PART_H
