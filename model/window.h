#ifndef WINDOW_H
#define WINDOW_H

#include <QPoint>

// a class which represents windows in the house facade
class Window{
public:
    // data functions
    virtual QPoint& getPosition() = 0;
    virtual int& getWidth() = 0;
    virtual int& getHeight() = 0;
    // destructor
    virtual ~Window(){}
protected:
   QPoint position;
   int width;
   int height;
};

#endif // WINDOW_H
