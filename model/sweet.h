#ifndef SWEET_H
#define SWEET_H

#include "model/candy.h"

// a class to represent to sweet candy
class Sweet : public Candy
{
public:
    Sweet(int, int, QPoint);
    ~Sweet(){}
    int& getWidth() override;
    int& getHeight() override;
    QPoint getPosition() override;
    int value() override;

};

#endif // SWEET_H
