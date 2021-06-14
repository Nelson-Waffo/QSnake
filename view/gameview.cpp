#include "gameview.h"

// constructor
GameView::GameView(QWidget *parent) : QMainWindow(parent)
{
    // initialise the old position
    oldSnakePosition = LVMeta::iniPosition;
    // initialise the score and time variable
    score = LVMeta::start_score;
    time = LVMeta::game_duration;
    // give the game focus: the main widget on its page
    this->setFocus();
    // speed of the snake
     speed = LVMeta::speed;

    // create tools
    // instantiate the tool bar
    toolbar = new QToolBar(tr("File"), this);
    toolbar->setAllowedAreas(Qt::TopToolBarArea);
    // create the tool bar
    createToolbar();
    // create the central widget
    createCentralWidget();

    // game animation
    gameLoopTimer = new QTimer(this);
    this->connect(gameLoopTimer, &QTimer::timeout, [=](){
        // update the score
        score = game->getScore();
        thescore->setText("Score: " + QString::number(score));
        // display the snake speed
        thespeed->setText("1 Frame Per " + QString::number(LVMeta::speed) + " ms");
        // call the paintEvent to paint the game class periodically
        // update is better than repaint because it allows qt to optimize speed and prevent flicker
        game->update(); // game loop
    });

    // a timer for the game duration
    time_timer = new QTimer(this);
    this->connect(time_timer, &QTimer::timeout, [=](){
        // update the score
        time -= 1; // minius 1 second
        thetime->setText("Time: " + QString::number(time));
        // update current time for the game
        game->setCurrentTime(time);
        // verify death of the snake
        game->verifyState();
        // update the speed of the game
        game->updateSpeed();

        // update the snake speed if the a certain number of
        // candies have been consumed. the snake gains speed
        // the more it eats candies
        if(speed != LVMeta::speed){
            // Meta::speed has changed at this point
            gameLoopTimer->stop();
            gameLoopTimer->start(LVMeta::speed);
            speed = LVMeta::speed;
        }
        if(time <= 0) time_timer->stop();
    });

    // stop the time timer if the game is over
    this->connect(game, &Game::stopTimer, [=](){
        time_timer->stop();
    });
}

// destructor for the game view
GameView::~GameView()
{
    gameLoopTimer->stop();
    time_timer->stop();
}

// a function which creates the central widget
void GameView::createCentralWidget()
{
    // instantiate the game widgets
    gameDisplay = new QGroupBox("Snake Game",this);
    // create the actual widget which contains the snake game
    game = new Game(this);
    game->setMinimumSize(LVMeta::display_width, LVMeta::display_height);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(game);
    gameDisplay->setLayout(layout);
    gameInfo = new QGroupBox("Snake Info",this);
    // dimensions and font for the game UI
    gameDisplay->setGeometry(0,0,LVMeta::display_width, LVMeta::display_height);
    gameInfo->setGeometry(LVMeta::display_width,0,LVMeta::info_width,LVMeta::info_height);
    gameInfo->setMinimumSize(LVMeta::info_width,LVMeta::info_height);
    gameDisplay->setStyleSheet("font-weight: bold; font-size: 16px; font-family: Georgia; color: blue;");
    gameInfo->setStyleSheet("font-weight: bold; font-size: 20px; font-family: Times New Roman; color: blue;");
    createInfoLayout();
    // create the main layout for the game UI
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* hbox = new QHBoxLayout(this);
    hbox->addWidget(gameDisplay);
    hbox->addWidget(gameInfo);
    centralWidget->setLayout(hbox);
    this->setCentralWidget(centralWidget);
}

// a function to start the timer
void GameView::initialiseElements()
{
    gameLoopTimer->start(LVMeta::speed);
    time_timer->start(LVMeta::second);
    // set the initial position of the snake
    oldSnakePosition = LVMeta::iniPosition;
}

// a function which creates a tool bar
void GameView::createToolbar()
{
    // restart action
    restartAction = new QAction("restart", this);
    this->connect(restartAction, &QAction::triggered, [=](){
        // reset the speed
        LVMeta::speed = LVMeta::initial_game_speed;
        this->restartGame();
    });
    toolbar->addAction(restartAction);
    toolbar->addSeparator();

    // resume action
    resumeAction = new QAction("resume", this);
    this->connect(resumeAction, &QAction::triggered, [=](){
        this->resumeGame();
    });
    toolbar->addAction(resumeAction);
    toolbar->addSeparator();

    // pause action
    pauseAction = new QAction("pause", this);
    this->connect(pauseAction, &QAction::triggered, [=](){
        this->pauseGame();
    });
    toolbar->addAction(pauseAction);
    toolbar->addSeparator();

    // quit button
    quitAction = new QAction("quit", this);
    // return to the first page
    this->connect(quitAction, &QAction::triggered, [=](){
        // display a confirmation dialog
        QMessageBox messageBox; // code taken from QMessageBox of Qt
        messageBox.setStyleSheet("font-weight: bold; font-size: 14px; font-family: Georgia; color: green;");
        messageBox.setText("Do you really want to return to the main page?");
        messageBox.setInformativeText("Are you sure?");
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messageBox.setDefaultButton(QMessageBox::No);
        int ret = messageBox.exec();
        switch (ret) {
          case QMessageBox::Yes:
            // reset the speed
               LVMeta::speed = LVMeta::initial_game_speed;
               // stop timers before leaving
               gameLoopTimer->stop();
               time_timer->stop();
               // reset the time
               time = LVMeta::game_duration;
               score = LVMeta::start_score;
               thescore->setText("Score: " + QString::number(score));
               thetime->setText("Time: " + QString::number(time));
               // 1) clean up the game
               game->resetGame();
               // 2) quit and display first page
               emit firstPage();
               break;
          case QMessageBox::No:
               // do not leave
               return;
          default:
               // should never be reached
               break;
        }
    });
    toolbar->addAction(quitAction);
    toolbar->addSeparator();
    // change game colour
    colorAction = new QAction("change color", this);
    this->connect(colorAction, &QAction::triggered, [=](){
        // change the colour of the game
        game->setBackgroundColor();
    });
    toolbar->addAction(colorAction);
    // add the tool bar to the main window
    this->addToolBar(toolbar);
}

// a function which creates the info layout
void GameView::createInfoLayout()
{
    // label for the score
    thescore = new QLabel(this);
    thescore->setText("Score: " + QString::number(score));
    // label for the game duration
    thetime = new QLabel(this);
    thetime->setText("Time: " + QString::number(time));
    // the speed of the snake
    thespeed = new QLabel(this);
    thespeed->setText("One Frame Per " + QString::number(LVMeta::speed) + " ms");
    // layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(thescore);
    layout->addWidget(thetime);
    layout->addWidget(thespeed);
    // set the layout for the game info
    gameInfo->setLayout(layout);
}

// a function to start the game
QTimer* GameView::getTimer()
{
    // start the timer
    return gameLoopTimer;

}

// a fucntion to pause the game
void GameView::pauseGame()
{
    gameLoopTimer->stop();
    time_timer->stop();
    game->pauseGame();
}

// a function to resume the game
void GameView::resumeGame()
{
    gameLoopTimer->start(LVMeta::speed);
    time_timer->start(LVMeta::second);
    game->resumeGame();
}

// a function to restart the game
void GameView::restartGame()
{
    // initialise the old position
    oldSnakePosition = LVMeta::iniPosition;
    // game loop timer
    gameLoopTimer->start(LVMeta::speed);
    // time timer
    time_timer->start(LVMeta::second);
    // reset the time
    time = LVMeta::game_duration;
    score = LVMeta::start_score;
    thescore->setText("Score: " + QString::number(score));
    thetime->setText("Time: " + QString::number(time));
    // 1) clean up the game
    game->resetGame();
}

// a function used to transmit user events to the model via the controller.
void GameView::keyPressEvent(QKeyEvent *event)
{
    if(game && game->getScore() < LVMeta::max_points){
        // commands to move the snake around based on user input
        if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left){
            if(oldSnakePosition != Position::Right){
                game->transmitUserEvents(Position::Left);
                // next time the execution enters here, old position will be:
                oldSnakePosition = Position::Left;
            }
        }
        else if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right){
            if(oldSnakePosition != Position::Left){
                game->transmitUserEvents(Position::Right);
                oldSnakePosition = Position::Right;
            }
        }
        else if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up){
            if(oldSnakePosition != Position::Down){
                 game->transmitUserEvents(Position::Up);
                 oldSnakePosition = Position::Up;
            }
        }
        else if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down){
            if(oldSnakePosition != Position::Up){
                game->transmitUserEvents(Position::Down);
                oldSnakePosition = Position::Down;
            }
        }
    }
}
