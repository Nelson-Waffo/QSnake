#ifndef WALL_H
#define WALL_H

#include <QPoint>
#include <QString>

// a abstract class for walls
class Wall{
public:
    // data functions
    virtual QPoint& getPosition() = 0;
    virtual int& getWidth() = 0;
    virtual int& getHeight() = 0;
    virtual QString& getType() = 0;
    // destructor
    virtual ~Wall(){}
protected:
    QPoint position;
    int width;
    int height;
    QString type;
};

#endif // WALL_H
