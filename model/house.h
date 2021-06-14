#ifndef HOUSE_H
#define HOUSE_H

#include "model/wall.h"
#include "model/window.h"
#include <QDebug>
#include <QList>

// a class which defines a house
class House{
public:
    // data functions
    virtual QList<Wall*>& getWalls() = 0;
    virtual QList<Window*>& getWindows() = 0;
    virtual int& getWidth() = 0;
    virtual int& getHeight() = 0;
    // destructor
    virtual ~House(){
        // destroy wall data
        for(QList<Wall*>::iterator iter = walls.begin();
            iter != walls.end(); ++iter){
            delete *iter;
        }
        // destroy windows data
        for(QList<Window*>::iterator iter = windows.begin();
            iter != windows.end(); ++iter){
            delete *iter;
        }
    }
protected:
    QList<Wall*> walls;
    QList<Window*> windows;
    int width; int height;
};

#endif // HOUSE_H
