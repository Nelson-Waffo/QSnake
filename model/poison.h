#ifndef POISON_H
#define POISON_H

#include "model/candy.h"

// a class used to render poisonous candies
class Poison : public Candy
{
public:
    Poison(int, int, QPoint);
    ~Poison(){}
    int& getWidth() override;
    int& getHeight() override;
    QPoint getPosition() override;
    int value() override;
};

#endif // POISON_H
