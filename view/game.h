#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QRandomGenerator>
#include <QTimer>

#include "controller/housecontroller.h"
#include "controller/snakecontroller.h"
#include "controller/candycontroller.h"

#include "meta/meta.h"

// a class which displays the snake game
class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget* parent = nullptr);
    ~Game() override;
    // render the house
    void renderHouseFacade(QPainter*);

    // render house walls
    void renderHouseWalls(QPainter*);

    // render house windows
    void renderHouseWindows(QPainter*);

    // a function to render the snake
    void renderSnake(QPainter*);
    // a function to render candies
    void renderCandies(QPainter*);
    // a funtion which display the death message
    void renderFinalText(QPainter*, const QString&);
    // a function to reset the game
    void resetGame();
    // a function which returns the snake state
    State getSnakeState();
    // a function to change the colours of the game
    void setBackgroundColor();
    // a function used to transmit user events to the model via the controller
    void transmitUserEvents(Position p);
    // a function to gather the score
    int getScore();
    // a function to update the current time
    void setCurrentTime(int);
    // a function to verify the snake state and conclude
    void verifyState();
    // a function to pause the game
    void pauseGame();
    // a function used to resume the game
    void resumeGame();
    // a function to update the speed of the game
    void updateSpeed();
    // QWidget interface
signals:
    void stopTimer();
protected:
    // a function used to draw on the game widget
    void paintEvent(QPaintEvent *event)override;
private:
    HouseController * houseController;
    SnakeController* snakeController;
    CandyController* candyController;
    QString facadeColour;
    // a variable that store the current time
    int current_time;
    // collision timer
    QTimer* collisionTimer;
};

#endif // GAME_H
