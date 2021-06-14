#include "game.h"
#include <QDebug>

// a fucntion which provides a colour for the facade
QString getColour(){
    int value = QRandomGenerator::global()->bounded(0, 100);
    if(value % 5 == 0){
        return "lightblue";
    }
    else if(value % 3 == 0){
        return "lightgreen";
    }
    else{
        return "pink";
    }
}

// constructor for the game widget
Game::Game(QWidget* parent) : QWidget(parent)
{
    houseController = new HouseController;
    snakeController = new SnakeController;
    candyController = new CandyController;
    facadeColour = getColour();
    // intial time
    current_time = LVMeta::game_duration;
    // collision timer
    collisionTimer = new QTimer(this);
    this->connect(collisionTimer, &QTimer::timeout, [=](){
        // detect collisions with candies
        snakeController->detectCollisions();
    });
    collisionTimer->start(LVMeta::collision_timer);
}

// destructor for the game widget
Game::~Game()
{
    collisionTimer->stop();
    // release all resources
    delete houseController;
    delete snakeController;
    delete candyController;
}

// a function which draws on the game widget
void Game::paintEvent(QPaintEvent *)
{
    // with "this" the painter paints this widget
    QPainter painter(this);
    QPen pen(Qt::blue);
    pen.setWidth(1);
    painter.setPen(pen);

    // rendering of the house facade
    painter.save();
    this->renderHouseFacade(&painter);
    painter.restore();

    // rendering of candies
    painter.save();
    this->renderCandies(&painter);
    painter.restore();

    // rendering of the snake
    painter.save();
    this->renderSnake(&painter);
    painter.restore();

    // rendering of the house walls
    painter.save();
    this->renderHouseWalls(&painter);
    painter.restore();

    // rendering of the house windows
    painter.save();
    this->renderHouseWindows(&painter);
    painter.restore();

    // render death text when necessary
    if(this->getSnakeState() == State::Dead){
         painter.save();
         this->renderFinalText(&painter, "YOU HAVE LOST. PLEASE TRY AGAIN!");
         painter.restore();
         // stop the time timer
         emit stopTimer();
     }

    // render death text when necessary
    if(this->getSnakeState() == State::Winner){
         painter.save();
         this->renderFinalText(&painter, "YOU BROKE OUT! CONGRATULATIONS!");
         painter.restore();
         // stop the time timer
         emit stopTimer();
     }
    painter.end();   
}

// a funtion which display the death message
void Game::renderFinalText(QPainter* painter, const QString& message){
    // show a message to the user
    painter->setPen(Qt::black);
    painter->setFont(QFont("Georgia", 19));
    QFont f = painter->font();
    f.setBold(true);
    painter->setFont(f); // bold font
    painter->drawText(LVMeta::display_width/25, (3*LVMeta::display_height)/8, message);
}

// a fucntion used to render the house
void Game::renderHouseFacade(QPainter * painter)
{
    // render the facade of the house
    QBrush greenBrush((QColor(facadeColour)));
    QBrush whiteBrush(Qt::white);
    House* house = houseController->getHouse();
    // draw the facade of the house
    int display_width = house->getWidth() / LVMeta::cell;
    int display_height = house->getHeight() / LVMeta::cell;
    painter->setPen(Qt::NoPen);
    for(int j = 0; j < display_width; j++){
        for(int k = 0; k < display_height; ++k){
            painter->setBrush(whiteBrush);
            painter->drawRect(j * LVMeta::cell, k * LVMeta::cell, LVMeta::cell, LVMeta::cell);
            painter->setBrush(greenBrush);
            painter->drawRect(j * LVMeta::cell, k * LVMeta::cell, LVMeta::cell-2, LVMeta::cell-2);
        }
    }
}

// a function which renders walls of the house
void Game::renderHouseWalls(QPainter * painter)
{
    // render walls of the house
    House* house = houseController->getHouse();
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(Qt::black);
    Wall* wall;
    for(int i = 0; i < house->getWalls().size(); ++i){
        wall = house->getWalls().at(i);
        painter->drawRoundedRect(wall->getPosition().x(), wall->getPosition().y(), wall->getWidth(), wall->getHeight(), 10, 20);
    }
}

// a function which renders windows of the house
void Game::renderHouseWindows(QPainter * painter)
{
    // render the windows of the house
    House* house = houseController->getHouse();
    QString color = "blue";
    QString lightColor = "lightblue";
    if(facadeColour == "lightblue"){
        color = "red";
        lightColor = "white";
    }
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    Window* window;
    for(int i = 0; i < house->getWindows().size(); ++i){
        window = house->getWindows().at(i);
        painter->setBrush(QColor(color));
        painter->drawRoundedRect(window->getPosition().x(), window->getPosition().y(), window->getWidth(), window->getHeight(), 10, 20);
        painter->setBrush(QColor(lightColor));
        painter->drawRoundedRect(window->getPosition().x() + LVMeta::cell, window->getPosition().y() + LVMeta::cell, window->getWidth() - (LVMeta::cell * 2), window->getHeight( ) - (LVMeta::cell * 2), 10, 20);
    }
}

// a function to render the snake
void Game::renderSnake(QPainter * painter)
{
    // render snake parts
    // use the dark blue colour for painting
    painter->setPen(Qt::NoPen);
    // snake color
    QColor snakeColor = facadeColour == "lightgreen" ? QColor(Qt::darkRed) : QColor(Qt::darkGreen);
    // drawing of the snake in the widget
    Snake* snake = snakeController->getSnake();
    // display the parts
    Part* part;
    for(int i = 0; i < snake->getParts().size(); ++i){
        // get one part
        part = snake->getParts().at(i);
        // display the part
        painter->setBrush(Qt::white);
        painter->drawRect(part->getPosition().x(), part->getPosition().y(), part->getWidth(), part->getHeight());
        painter->setBrush(snakeColor);
        painter->drawRect(part->getPosition().x(), part->getPosition().y(), part->getWidth() - 2, part->getHeight() - 2);
    }
}

// a function to render candies
void Game::renderCandies(QPainter * painter)
{
    // no pen needed
    painter->setPen(Qt::NoPen);
    // colour for the brush of the painter
    QColor sweetColour(102, 0, 204);
    QColor poisonColour(77, 26, 0);
    QFont font = painter->font();
    font.setPixelSize(14);
    painter->setFont(font);
    // get the candy instance
    QList<Candy*> candies = candyController->getCandies();
    // make sure the candies are not under the snake
    Snake* snake = SnakeController::getSnake();
    for(QList<Candy*>::iterator iter1 = candies.begin();
        iter1 != candies.end(); ++iter1){
        for(QList<Part*>::iterator iter2 = snake->getParts().begin();
            iter2 != snake->getParts().end(); ++iter2){
            if((*iter1)->getPosition().x() == (*iter2)->getPosition().x() &&
               (*iter1)->getPosition().y() == (*iter2)->getPosition().y() ){
                // do not render a candy under the snake
               if((*iter2) == snake->getHead()) continue;
                candyController->getCandies().clear();
                return;
            }
        }
    }
    // render candy
    for(QList<Candy*>::iterator iter = candies.begin();
        iter != candies.end(); ++iter){
        Candy * candy = (*iter);
        if(candy->value() == Value::Grow){
            painter->setBrush(sweetColour);
            painter->drawEllipse(candy->getPosition().x(), candy->getPosition().y(),
                                 candy->getWidth(), candy->getHeight());
        }else if(candy->value() == Value::Shrink){
              painter->setBrush(poisonColour);
              painter->drawEllipse(candy->getPosition().x(), candy->getPosition().y(),
                                   candy->getWidth(), candy->getHeight());
              painter->setPen(Qt::white);
              painter->drawText(candy->getPosition().x(), candy->getPosition().y(),
                                   candy->getWidth(), candy->getHeight(), Qt::AlignCenter ,"P");
        }

    }
}

// a fucntion used to reset the game
void Game::resetGame()
{
    // delete houseController;
    delete snakeController;
    snakeController = new SnakeController;
    facadeColour = getColour();
    // clear the candies
    candyController->getCandies().clear();
}

// the function returns the snake state
State Game::getSnakeState()
{
   if(snakeController)return snakeController->getSnakeState();
   return State::Dead;
}

// a function to change the colours of the game
void Game::setBackgroundColor()
{
    QString oldColour = facadeColour;
    // get a colour
    facadeColour = getColour();
    while(facadeColour == oldColour){
        // only return a different colour than the previous
        facadeColour = getColour();
    }
}

// a function to transmit user events
void Game::transmitUserEvents(Position p)
{
    // drawing of the snake in the widget
    Snake* snake = snakeController->getSnake();
    // pass the user event
    snake->getPosition() = p;
}

// a function used to collect the score
int Game::getScore()
{
    if(snakeController)return snakeController->getScore();
    return LVMeta::start_score;
}

// a variable to update the current time
void Game::setCurrentTime(int time)
{
    current_time = time;

}

// a fucntion that verifies snake state and conclude
void Game::verifyState()
{
     Snake* snake = snakeController->getSnake();
    // check time
    if(current_time <= 0 && this->getScore() < LVMeta::max_points){
        // the game is over
        if(snake) snake->getState() = State::Dead;
        return;
    }
    if(current_time > 0 && this->getScore() >= LVMeta::max_points){
        // the game is over and the player won
        if(snake) snake->getState() = State::Winner;
    }
}

// a function to pause the game
void Game::pauseGame()
{
    Snake* snake = snakeController->getSnake();
    if(snake) snake->getState() = State::Still;
}

// a fucntion used to restart the game
void Game::resumeGame()
{
    Snake* snake = snakeController->getSnake();
    if(snake && snake->getState() == State::Still){
        snake->getState() = State::Alive;
    }
}

// a function to update the speed of the game
void Game::updateSpeed()
{
    // the score variables
    int score = 0;
    static int oldScore = 0;
    if(snakeController) score = snakeController->getScore();
    if(score != oldScore && score % 10 == 0){
        // increase speed each time a user collects 10 points
        if(LVMeta::speed <= (LVMeta::speed / 2)) return;
        LVMeta::speed -= LVMeta::speed_increment;
        // update the speed of the snake
        Snake* snake = snakeController->getSnake();
        if(snake) snake->updateSnakeSpeed();
        // block unwanted repeats
        oldScore = score;
    }
}
