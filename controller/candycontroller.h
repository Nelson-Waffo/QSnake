#ifndef CANDYCONTROLLER_H
#define CANDYCONTROLLER_H

#include "model/sweet.h"
#include "model/poison.h"
#include "controller/housecontroller.h"
#include "controller/snakecontroller.h"

#include <QRandomGenerator>

#include "meta/meta.h"

// a class responsible for managing candies
// helps the view display candies
// create candy data and updates candy's data in the model
class CandyController
{
public:
    CandyController();
    ~CandyController();
    // a fucntion to return the instance of the candy
    static QList<Candy*>& getCandies();

private:
    // check the position of the candy
    static bool verifyPosition(int, int);
    static void createCoordinates(int&, int&, int, int, int, int);
    static QList<Candy*> candies;
};

#endif // CANDYCONTROLLER_H
