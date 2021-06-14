#ifndef PYTHON_H
#define PYTHON_H

#include "model/snake.h"
#include <QTimer>

// a class which represents a python
class Python : public QObject, public Snake
{
    Q_OBJECT
public:
    // constructor
    Python(QList<Part*>, House*,  QList<Candy*>&);
    QList<Part*>& getParts() override;
    Position& getPosition() override;
    State& getState() override;
    // a function which delivers the head of the snake
    Part*& getHead() override;
    // a function used to deliver a reference to the candy
    QList<Candy*>& getCandies() override;
    void clearCandies() override;
    // a function which returns the house
    House*& getHouse()override;
    // a fucntion to update the speed of the snake
    void updateSnakeSpeed() override;
    // destructor
    ~Python()override;
public slots:
    void move()override;
private:
    void moveHelper(Position);

private:
    QTimer* timer;
};

#endif // PYTHON_H
