#include "firmwall.h"

FirmWall::FirmWall(QPoint p, int w, int h, QString t)
{
    position = p; width = w; height = h; type = t;
}

QPoint &FirmWall::getPosition()
{
    return position;
}

int &FirmWall::getWidth()
{
    return width;
}

int &FirmWall::getHeight()
{
    return height;
}

QString &FirmWall::getType()
{
    return type;
}
