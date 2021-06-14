#include "snakecontroller.h"

// intiialise the snake
Snake * SnakeController::snake = nullptr;
int SnakeController::score = LVMeta::start_score;

// constructor
SnakeController::SnakeController()
{
    // create the snake
    // this->getSnake();
}

// destructor
SnakeController::~SnakeController()
{
    score = LVMeta::start_score;
    delete snake;
    snake = nullptr;
}

// a fucntion whcih delivers the snake instance
Snake *SnakeController::getSnake()
{
    if(snake == nullptr){
         // positions
         int posX = LVMeta::display_width / 2;
         int posY = (LVMeta::display_height / 4);
         // get the house instance
         House* house = HouseController::getHouse();

         // create the basic, initial parts of the snake
         Part* inch1 = new Inch(LVMeta::cell, LVMeta::cell, QPoint(posX, posY));
         posX += LVMeta::cell;
         Part* inch2 = new Inch(LVMeta::cell, LVMeta::cell, QPoint(posX, posY));
         posX += LVMeta::cell;
         Part* inch3 = new Inch(LVMeta::cell, LVMeta::cell, QPoint(posX, posY));
         QList<Part*> parts;

         // body of the snake
         parts.push_front(inch1);
         parts.push_front(inch2);
         // head of the snake: inch 3
         parts.push_front(inch3); // index 0
         // candies of the snake
         QList<Candy*> candies = CandyController::getCandies();
         // create the python snake with its parts
         snake = new Python(parts, house, candies);
    }
    return snake;
}

// a fucntion which detects collisions and makes the snake grow
void SnakeController::detectCollisions()
{
    if(snake == nullptr) return;
    // collisions are not checked after the game is won
    if(snake->getState() == State::Winner){
        return;
    }
    // future head coordinates
    int futureX = snake->getHead()->getPosition().x();
    int futureY = snake->getHead()->getPosition().y();
    if(snake->getPosition() == Position::Down){
        futureY += LVMeta::cell;
    }
    else if(snake->getPosition() == Position::Up){
        futureY -= LVMeta::cell;
    }
    else if(snake->getPosition() == Position::Right){
        futureX += LVMeta::cell;
    }
    else if(snake->getPosition() == Position::Left){
        futureX -= LVMeta::cell;
    }

    // check for collisisions with candies
    // go through the candies and check if one of them is equal to
    // the head of the snake
    QList<Candy*> candies = snake->getCandies();
    for(QList<Candy*>::iterator iter = candies.begin();
        iter != candies.end(); ++iter){
        Candy * candy = *iter;
        if(candy->getPosition().x() == futureX &&
               candy->getPosition().y() == futureY){
            // play collision sound
            // grow the snake
            if(candy->value() == Value::Grow){
                // play sweet sound
                media.setMedia(QUrl(LVMeta::sweet_sound));
                media.play();
                // get the head of the snake
                // create the new head
                Part * newHead = new Inch(LVMeta::cell, LVMeta::cell, QPoint(futureX, futureY));
                // make the snake grow
                snake->getParts().push_front(newHead);
                // update the head
                snake->getHead() = newHead;
                // update the score
                score += LVMeta::scoring;
            }
            else if(candy->value() == Value::Shrink){
                // play poison sound
                media.setMedia(QUrl(LVMeta::poison_sound));
                media.play();
                // make the snake shrink
                // get the tail of the snake
                Part* part = snake->getParts().at(snake->getParts().size()-1);
                // cut the tail of the snake
                snake->getParts().removeOne(part);
                // release memory
                delete part;
                // update score
                score -= LVMeta::scoring;
                // check the height of the snake and the player and determine health of
                // the snake
                if(snake->getParts().size() < LVMeta::snake_min_height || score < 0){
                    // the snake is dead at this point
                    snake->getState() = State::Dead;
                }
            }
            // clear the candies
            snake->clearCandies(); // release memory of the candies
            CandyController::getCandies().clear(); // size = 0
            // create new candies
            snake->getCandies() = CandyController::getCandies();
            break;
        }
    }

    // detect collisions with windows
    // get windows
    QList<Window*> windows = snake->getHouse()->getWindows();
    futureX = snake->getHead()->getPosition().x();
    futureY = snake->getHead()->getPosition().y();

    int futureWidth = LVMeta::cell; int futureHeight = LVMeta::cell;

    // go through the windows and search for collisions
    for(QList<Window*>::iterator iter = windows.begin();
        iter != windows.end(); ++iter){
        // check collisions
        int winX = (*iter)->getPosition().x();
        int winY = (*iter)->getPosition().y();
        int winW = (*iter)->getWidth();
        int winH = (*iter)->getHeight();

        if((((futureX + futureWidth > winX && winX >= futureX) || (futureX < winX + winW && futureX > winX)) && (futureY >= winY && futureY < winY + winH) )
        ||(( (futureY + futureHeight > winY && winY + winH > futureY) || (futureY < winY + winH && futureY > winY)) && (futureX + futureWidth > winX && futureX < winX + winW))){
            // the snake is dead at this point
            snake->getState() = State::Dead;
            break;
        }
    }

    // check if the snake choked
    QList<Part*> parts = snake->getParts();
    parts.removeOne(snake->getHead());
    for(QList<Part*>::iterator iter = parts.begin();
        iter != parts.end(); ++iter){
        Part * part = *iter;
        if(part->getPosition().x() == futureX &&
               part->getPosition().y() == futureY){
            // the snake is dead at this point
            snake->getState() = State::Dead;
            break;
        }
    }

    // check for wall collisions
    // get walls
    QList<Wall*> walls = snake->getHouse()->getWalls();
    for(QList<Wall*>::iterator iter = walls.begin();
        iter != walls.end(); ++iter){
        int wallX = (*iter)->getPosition().x();
        int wallY = (*iter)->getPosition().y();
        int wallW = (*iter)->getWidth();
        int wallH = (*iter)->getHeight();

        if((((futureX + futureWidth > wallX && wallX >= futureX) || (futureX < wallX + wallW && futureX > wallX)) && (futureY >= wallY && futureY < wallY + wallH) )
        ||(( (futureY + futureHeight > wallY && wallY + wallH > futureY) || (futureY < wallY + wallH && futureY > wallY)) && (futureX + futureWidth > wallX && futureX < wallX + wallW))){
            // the snake is dead at this point
            snake->getState() = State::Dead;
            break;
        }
    }
}

// a function which returns the score of the game
int SnakeController::getScore()
{
    return score;
}

// function to return the state of the snake
State SnakeController::getSnakeState()
{
    return snake->getState();
}
