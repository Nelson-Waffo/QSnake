#ifndef CABIN_H
#define CABIN_H

#include "model/house.h"

// Cabin is a house
class Cabin : public House
{
public:
    Cabin(int, int, QList<Wall *>&, QList<Window*>&);
    ~Cabin();
    QList<Wall*>& getWalls() override;
    QList<Window*>& getWindows() override;
    int& getWidth() override;
    int& getHeight() override;
};

#endif // CABIN_H
