#include "candycontroller.h"

// initialise the candy
QList<Candy*> CandyController::candies;

// constructor for the candy
CandyController::CandyController()
{
}

CandyController::~CandyController()
{
    for(QList<Candy*>::iterator iter = candies.begin();
        iter != candies.end(); ++iter){
        delete *iter;
    }
    candies.clear();
}

// a function which returns the candy
QList<Candy*>& CandyController::getCandies()
{
    if(candies.size() == 0){
         // create a sweet candy at a random position
        int x,y;
        createCoordinates( x, y, LVMeta::cell, LVMeta::display_width - LVMeta::cell, LVMeta::cell, LVMeta::display_height - LVMeta::cell);
        // now that the candy is not under any window create it and return it
        // by default a sweet is created
        Candy* candy = new Sweet(LVMeta::cell, LVMeta::cell, QPoint(x,y));
        candies.append(candy);

        // create 1 poisonous candy
        int a, b; // coordinates of the poisonous candy

        createCoordinates( a, b, x - LVMeta::range * LVMeta::cell, x + LVMeta::range * LVMeta::cell, y - LVMeta::range * LVMeta::cell, y + LVMeta::range * LVMeta::cell);
        if(a >= LVMeta::cell && a < LVMeta::display_width - LVMeta::cell && b >= LVMeta::cell &&
             b < LVMeta::display_height - LVMeta::cell && a != x && b != y){
            Candy* poison = new Poison(LVMeta::cell, LVMeta::cell, QPoint(a,b));
            candies.append(poison);
        }
        // create a second poisonous candy
        int c, d;
        createCoordinates( c, d, x - (1+LVMeta::range) * LVMeta::cell, x + (1+LVMeta::range) * LVMeta::cell, y - (1+LVMeta::range) * LVMeta::cell, y + (1+LVMeta::range) * LVMeta::cell);
        if(c >= LVMeta::cell && c < LVMeta::display_width - LVMeta::cell && d >= LVMeta::cell &&
             d < LVMeta::display_height - LVMeta::cell && c != a && d != b && c != x && d != y){
            Candy* poison = new Poison(LVMeta::cell, LVMeta::cell, QPoint(c,d));
            candies.append(poison);
        }
    }
    return candies;
}

// a fucntion which makes sure that the candy isnt under a window
bool CandyController::verifyPosition(int x, int y)
{
    House* house = HouseController::getHouse();
    QList<Window*> windows = house->getWindows();
    // perform the check: candy should not land under a window or snake
    for(QList<Window*>::iterator iter = windows.begin();
        iter != windows.end(); ++iter){
        int windowX = (*iter)->getPosition().x();
        int windowWidth = (*iter)->getWidth();
        int windowY = (*iter)->getPosition().y();
        int windowHeight = (*iter)->getHeight();
        if(x >= windowX && x < windowX + windowWidth && y >= windowY &&
                y < windowY + windowHeight){
            // the candy is under the window
            return false;
        }
    }
    return true;
}

// a function used to calculate coordinates
void CandyController::createCoordinates(int & x, int & y, int xlow, int xhigh, int ylow, int yhigh)
{
    // create a sweet candy at a random position
    // x position taking into account the walls width
    x = QRandomGenerator::global()->bounded(xlow, xhigh);
    y = QRandomGenerator::global()->bounded(ylow, yhigh);
    // make sure the candy is well placed in the view
    x = x - (x % LVMeta::cell);
    y = y - (y % LVMeta::cell);
    // verify that the position is not under a window
    while(!verifyPosition(x, y)){
        // create new coordinates
        x = QRandomGenerator::global()->bounded(xlow, xhigh);
        y = QRandomGenerator::global()->bounded(ylow, yhigh);
        // make sure the candy is well placed in the view
        x = x - (x % LVMeta::cell);
        y = y - (y % LVMeta::cell);
    }
}
