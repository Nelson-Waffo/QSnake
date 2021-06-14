#include "view/mainview.h"

#include <QApplication>

#include <QList>
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainView w;
    w.show();
    return a.exec();

    /*
    QList<int> values;
    values.push_front(3);
    values.push_front(10);
    values.push_front(78);
    std::cout << values.at(0) << std::endl;
    */
}
