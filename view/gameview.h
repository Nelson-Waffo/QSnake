#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QGroupBox>
#include <QLayout>
#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>

#include "game.h"

// the widget is page which renders the game itself and
// the information about the game
class GameView : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView() override;
    // a fucntion to create the central widget
    void createCentralWidget();
    // a function to start the timer
    void initialiseElements();
    // a function to create a toolbar
    void createToolbar();
    // information layout
    void createInfoLayout();
    // a function to start the game
    QTimer* getTimer();
    // a fucntion to pause the game
    void pauseGame();
    // a function to resume the game
    void resumeGame();
    // a function to restart the game
    void restartGame();

signals:
    // display the first page
    void firstPage();
private:
    // a widget for the game display
    QGroupBox* gameDisplay;
    // a widget for the game information
    QGroupBox* gameInfo;
    // a reference to the widget that contains the snake game
    Game* game;
    // create the tool bar object
    QToolBar* toolbar;
    // create an action
    QAction* quitAction;
    QAction* resumeAction;
    QAction* pauseAction;
    QAction* colorAction;
    QAction* restartAction;

    // a variable to define game speed
    int speed;
    // timer for the game animation
    QTimer* gameLoopTimer;
    QTimer* time_timer;
    // a variable to store the score of the game
    int score;
    // a variable that contains the time
    int time;

    // label for the score
    QLabel* thescore;

    // a label to display the time
    QLabel* thetime;

    // a label for the speed of the snake
    QLabel* thespeed;

    // initial position: lazy solution (not recommended)
    Position oldSnakePosition;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMEVIEW_H
