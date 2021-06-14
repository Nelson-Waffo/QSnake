#include "housecontroller.h"

// the house instance
House * HouseController::house = nullptr;

// constructor
HouseController::HouseController()
{

}

// destructor
HouseController::~HouseController()
{
    delete house;
    house = nullptr;
}

// get the house instance
House *HouseController::getHouse()
{
    if(house == nullptr){
        // create the walls of the house. static data
        Wall* leftwall = new FirmWall(QPoint(0,0), LVMeta::cell, LVMeta::display_height, "firm");
        Wall* topwall = new FirmWall(QPoint(0,0), LVMeta::display_width, LVMeta::cell, "firm");
        Wall* bottomwall = new FirmWall(QPoint(0, LVMeta::display_height - LVMeta::cell), LVMeta::display_width, LVMeta::cell, "firm");
        Wall* rightwall = new FirmWall(QPoint(LVMeta::display_width - LVMeta::cell, 0), LVMeta::cell, LVMeta::display_height, "firm");
        QList<Wall*> walls;
        walls.push_back(leftwall);
        walls.push_back(topwall);
        walls.push_back(bottomwall);
        walls.push_back(rightwall);

        // create windows of the house (randomize) : static data
        Window* leftWindow = new SquareWindow(QPoint(LVMeta::cell * 5, LVMeta::cell * 16), LVMeta::cell * 5, LVMeta::cell * 5);
        Window* topWindow = new SquareWindow(QPoint(LVMeta::cell * 16, LVMeta::cell * 4), LVMeta::cell * 5, LVMeta::cell * 5);
         Window* centerWindow = new SquareWindow(QPoint(LVMeta::cell * 17, LVMeta::cell * 17), LVMeta::cell * 5, LVMeta::cell * 5);
        Window* rightWindow = new SquareWindow(QPoint(LVMeta::cell * 30, LVMeta::cell * 16), LVMeta::cell * 5, LVMeta::cell * 5);
        Window* bottomWindow = new SquareWindow(QPoint(LVMeta::cell * 16, LVMeta::cell * 31), LVMeta::cell * 5, LVMeta::cell * 5);
        QList<Window*> windows;
        windows.push_back(leftWindow);
        windows.push_back(topWindow);
        windows.push_back(centerWindow);
        windows.push_back(rightWindow);
        windows.push_back(bottomWindow);
        house = new Cabin(LVMeta::display_width, LVMeta::display_height, walls, windows);
    }
    return house;
}
