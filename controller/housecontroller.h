#ifndef HOUSECONTROLLER_H
#define HOUSECONTROLLER_H

#include "model/firmwall.h"
#include "model/squarewindow.h"
#include "model/cabin.h"

#include "meta/meta.h"

// a class which manages the house in the game
// responsible for creating and destroying data
// responsible for update the model and the view
// the class manages the house
class HouseController
{
public:
    HouseController();
    ~HouseController();
    static House* getHouse();
private:
    // the house instance
    static House * house;
};

#endif // HOUSECONTROLLER_H
