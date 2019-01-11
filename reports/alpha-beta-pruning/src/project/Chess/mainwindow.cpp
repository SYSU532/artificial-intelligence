#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/audios/back.mp3"));
    player->play();

    ui->setupUi(this);

    initActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initActions(){
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->helpButton, SIGNAL(clicked()), this, SLOT(help()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(exit()));
}

void MainWindow::showMainWindow(){
    this->show();
    player->play();
}

void MainWindow::start(){
    player->stop();
	this->hide();
    emit showGameWindow();
}

void MainWindow::help(){

}

void MainWindow::exit(){
    this->close();
}
