#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QStackedWidget>
#include <QFile>
#include <QDir>
#include <QByteArray>

#include "gameview.h"
#include "meta/meta.h"

// a class which contains the main window of the game
class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = nullptr);
    // a function to create the first window
    QWidget* createFirstPage();
    // a function to create the help page
    QWidget* createHelpPage();
    // a function to create the game page
    QWidget* createGamePage();
    ~MainView();
public slots:
    void gotoHelp();

private:

    // initial widget
    QStackedWidget* stack;
    // help page
    QWidget* helpPage;
    // first page
    QWidget* firstPage;
    // a game instance
    GameView* gameView;
};
#endif // MAINVIEW_H
