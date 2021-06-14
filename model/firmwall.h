#ifndef FIRMWALL_H
#define FIRMWALL_H

#include "wall.h"

// a class which defines firm walls
class FirmWall : public Wall
{
public:
    FirmWall(QPoint, int, int, QString);
    QPoint& getPosition() override;
    int& getWidth()override;
    int& getHeight()override;
    QString& getType()override;
};

#endif // FIRMWALL_H
