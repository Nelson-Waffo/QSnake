#include "python.h"

// constructor
Python::Python(QList<Part*> p, House * h, QList<Candy*>& c)
{
    // initialise elements of the snakes
    parts = p;
    house = h;
    candies = c;
    // set the end of the snake: the first element in the list
    head = p.at(0);
    // initially the snake moves to the right
    position = LVMeta::iniPosition;
    // and is alive
    state = State::Alive;
    // make the snake move
    timer = new QTimer();
    this->connect(timer, &QTimer::timeout, [=](){
        // make the snake move
        this->move();
    });
    timer->start(LVMeta::speed);
}

// a function which returns parts of the snake
QList<Part *>& Python::getParts()
{
    return parts;
}

// a function which returns the position of the snake
Position& Python::getPosition()
{
    return position;
}

// a function which returns the state of the snake
State &Python::getState()
{
    return state;
}

Part *&Python::getHead()
{
    return head;
}

// a getter for the candy
QList<Candy*>& Python::getCandies()
{
    return candies;
}

// a function used to release memory of the candies
void Python::clearCandies()
{
    // clear candies
    for(QList<Candy*>::iterator iter = candies.begin();
        iter != candies.end(); ++iter){
        Candy * candy = *iter;
        // remove from the list
        candies.removeOne(candy);
        // release memory
        delete candy;
    }
}

House *&Python::getHouse()
{
    return house;
}

// a fucntion to update the speed of the snake
void Python::updateSnakeSpeed()
{
    // update the speed of the snake with new speed value
    timer->stop();
    timer->start(LVMeta::speed);
}

// a function used to move the snake
void Python::move()
{
    // move the snake according to user input
    // if the snake is alive
    if(this->getState() == State::Alive || this->getState() == State::Winner)
        moveHelper(position);
}

// a function to help with the moving of parts
void Python::moveHelper(Position pos)
{
    // store the x and y position of the head
    int nextX = head->getPosition().x();
    int nextY = head->getPosition().y();
    for(QList<Part*>::iterator iter = parts.begin();
        iter != parts.end(); ++iter){
        if(*iter == head){
            // get the current y position of the head
            if(pos == Position::Up || pos == Position::Down){
                int y = (*iter)->getPosition().y();
                if(pos == Position::Up){
                      y -= LVMeta::cell;
                }else{
                      y += LVMeta::cell;
                }
                // move the head position
                (*iter)->getPosition().setY(y);
            }
            // right and left movements
            else if(pos == Position::Right || pos == Position::Left){
                int x = (*iter)->getPosition().x();
                if(pos == Position::Right){
                      x += LVMeta::cell;
                }else{
                      x -= LVMeta::cell;
                }
                // move the head position
                (*iter)->getPosition().setX(x);
            }
        }else{
            // get the y position of the next element
            int tempX = (*iter)->getPosition().x();
            int tempY = (*iter)->getPosition().y();
            // move the next element
            (*iter)->getPosition().setX(nextX);
            (*iter)->getPosition().setY(nextY);
            // update for the next part
            nextX = tempX;
            nextY = tempY;
        }
    }
}

// destructor
Python::~Python()
{
    timer->stop();
    delete timer;
}

