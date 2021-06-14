#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include "part.h"
#include "enums/position.h"
#include "enums/state.h"
#include "model/house.h"
#include "model/candy.h"

#include "meta/meta.h"

// a class which models the snake
class Snake{

public:
    virtual QList<Part*>& getParts() = 0;
    virtual Position& getPosition() = 0;
    virtual State& getState() = 0;
    virtual Part*& getHead() = 0;
    virtual House*& getHouse() = 0;
    virtual void updateSnakeSpeed() = 0;
    // a fucntion to access the candy
    virtual QList<Candy*>& getCandies() = 0;
    virtual void clearCandies() = 0;
    // destructor
    virtual ~Snake(){
        // destroy parts
        for(QList<Part*>::iterator iter = parts.begin();
            iter != parts.end(); ++iter){
            delete *iter;
        }
    }
public slots:
    // a function to move the snake
    virtual void move() = 0;

protected:
    // a variable to store the head of the snake to dictate its movement
    Part * head;
    // a snake consists of 3 or more parts
    QList<Part*> parts;
    // the snake has a position and a state
    Position position;
    State state;
    // the snake uses the house to check collisions with the house
    House * house;
    // the snake uses a candy to detect collisions with it
    QList<Candy*> candies;
};
#endif // SNAKE_H
