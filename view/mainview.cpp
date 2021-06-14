#include "mainview.h"
#include "ui_mainwindow.h"

#include <QDebug>

// constructor
MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
{
    // set window dimensions
    this->setGeometry(400, 100, LVMeta::display_width, LVMeta::display_height);

    // initialise the widget container
    stack = new QStackedWidget(this);

    // welcome page
    firstPage = createFirstPage();
    // help page
    helpPage = createHelpPage();
    // widget for the game area
    gameView = new GameView(this);

    // add widgets to the stack
    stack->addWidget(firstPage);
    stack->addWidget(helpPage);
    stack->addWidget(gameView);

    // set the current widget
    stack->setCurrentWidget(firstPage);

    // set the central widget for this app
    this->setCentralWidget(stack);

    // display of the first page containing the welcome
    this->connect(gameView, &GameView::firstPage, [=](){
        // set the current widget
        stack->setCurrentWidget(firstPage);
    });
}

// the function creates the first window
QWidget *MainView::createFirstPage()
{
    // create the title group box
    QGroupBox* titleBox = new QGroupBox("Title",this);
    titleBox->setStyleSheet("font-weight: bold; font-size: 14px; font-family: Georgia; color: blue;");
    titleBox->setAlignment(Qt::AlignCenter);
    titleBox->setMinimumSize(400, 80);
    QLabel * title = new QLabel("Snake Game", this);
    title->setStyleSheet("font-weight: bold; font-size: 26px; font-family: Georgia; color: green;");
    QVBoxLayout* titleLayout = new QVBoxLayout(this);
    titleLayout->setAlignment(Qt::AlignCenter);
    titleLayout->setSpacing(10);
    titleLayout->addWidget(title);
    titleBox->setLayout(titleLayout);

    // create the buttons group box
    QGroupBox* buttonsBox = new QGroupBox("Buttons", this);
    buttonsBox->setStyleSheet("font-weight: bold; font-size: 14px; font-family: Georgia; color: blue;");
    buttonsBox->setAlignment(Qt::AlignCenter);
     buttonsBox->setMinimumSize(400, 80);

     // start button
    QPushButton* startButton = new QPushButton("Start", this);
    startButton->setStyleSheet("font-weight: bold; font-size: 14px; font-family: Georgia; color: green; background-color: white;");
    this->connect(startButton, &QPushButton::clicked,[=](){
        // display the game window
        stack->setCurrentWidget(gameView);
        // start the timers of the game view
        gameView->initialiseElements();
    });

    // create the help button
    QPushButton* helpButton = new QPushButton("Help", this);
    helpButton->setStyleSheet("font-weight: bold; font-size: 14px; font-family: Georgia; color: green; background-color: white;");
    this->connect(helpButton, SIGNAL(clicked()), this, SLOT(gotoHelp()));

    // the layout for the buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout(this);
    buttonsLayout->setAlignment(Qt::AlignCenter);
    buttonsLayout->setSpacing(40);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(helpButton);
    buttonsBox->setLayout(buttonsLayout);

    // set up the first page
    QWidget* firstPage = new QWidget(this);
    firstPage->setStyleSheet("background-color: white;");
    QVBoxLayout* firstLayout = new QVBoxLayout(this);
    firstLayout->setAlignment(Qt::AlignCenter);
    firstLayout->addWidget(titleBox);
    firstLayout->addWidget(buttonsBox);
    firstLayout->setSpacing(20);
    firstPage->setLayout(firstLayout);
    return firstPage;
}

// a fucntion to create the help page
QWidget *MainView::createHelpPage()
{
    // create a layout for the back button
    QVBoxLayout* buttonLayout = new QVBoxLayout(this);
    buttonLayout->setAlignment(Qt::AlignLeft);
    // create the back button
    QPushButton* back = new QPushButton("Back",this);
    back->setStyleSheet("font-weight: bold; font-size: 14px; font-family: Georgia; color: green; background-color: white;");
    buttonLayout->addWidget(back);
    this->connect(back, &QPushButton::clicked, [=](){
            // display the first page again
            stack->setCurrentWidget(firstPage);
    });

    // create the group box for help message itself
    QGroupBox* helpBox = new QGroupBox("Help Message", this);
    helpBox->setMinimumSize(400, 300);
    helpBox->setStyleSheet("font-weight: bold; font-size: 14px; font-family: Georgia; color: blue;");

    // create the label for the help
    QLabel* message = new QLabel(this);
    message->setStyleSheet("font-weight: normal; font-size: 16px; font-family: Georgia; color: black;");

    // step 0: create a directory (the current directory)
    QDir directory =  QDir::current();
    // step 1: create a handle to a file named help.txt
    QString path = directory.path() + "/help.txt";
    QFile file(path);

    // first of all: open the file for reading
   if(!file.open(QFile::ReadOnly | QFile::Truncate)) return back;
    // container for the contents of the file
    QString contents;
    // read the file
    while(!file.atEnd()){ // while the end of the file has not been reached
        // read one line
        QByteArray line = file.readLine();
        // store the line   // conversion from QByteArray to QString
        contents.append(QString::fromUtf8(line));
    }
    // set the text for the help page
    message->setText(contents);
    // create a layout for the help group box
    QVBoxLayout* helpLayout = new QVBoxLayout(this);
    helpLayout->setAlignment(Qt::AlignCenter);
    helpLayout->addWidget(message);
    helpBox->setLayout(helpLayout);

    // create a layout for the help page
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(helpBox);
    layout->addLayout(buttonLayout);

    // create the main widget for the help page
    QWidget* helpPage = new QWidget(this);
    helpPage->setLayout(layout);
    return helpPage;
}

MainView::~MainView()
{
}

// a function which triggers the display of the help
void MainView::gotoHelp()
{
    // display help page
    stack->setCurrentWidget(helpPage);
}

