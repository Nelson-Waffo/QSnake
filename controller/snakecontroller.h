#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include <QMediaPlayer>
#include "model/python.h"
#include "model/inch.h"
#include "housecontroller.h"
#include "candycontroller.h"

#include "enums/value.h"
#include "meta/meta.h"

// class responsible for managing the snake
// that includes creating, deleting the snake as well
// as overseeing the interactions between the snake and the world
// as it manages the interacts and it therefore also manages the game score
class SnakeController
{
public:
    SnakeController();
    ~SnakeController();
    // a function to deliver the snake instance to the renderer
    static Snake* getSnake();
    // collisions between the snake and the candy
    void detectCollisions();
    static int getScore();
    // a fucntion whih returns the game state
    State getSnakeState();

private:
   static Snake * snake;
   static int score;
   QMediaPlayer media;
};

#endif // SNAKECONTROLLER_H
