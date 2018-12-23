#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h = HillClimbing::getInstance();
    ann = Annealing::getInstance();
    ui->climb_widget->installEventFilter(this);
    ui->anneal_widget->installEventFilter(this);
    cThread = new QThread(this);
    aThread = new QThread(this);
    ct = new ClimbThread(nullptr);
    at = new AnnealThread(nullptr);
    ct->moveToThread(cThread);
    at->moveToThread(aThread);
    connect(this, &MainWindow::startClimb, ct, &ClimbThread::run);
    connect(this, &MainWindow::startAnneal, at, &AnnealThread::run);
    connect(ct, &ClimbThread::running, this, &MainWindow::receiveClimbing);
    connect(at, &AnnealThread::running, this, &MainWindow::receiveAnnealing);
    connect(ct, &ClimbThread::complete, this, &MainWindow::receiveClimbComplete);
    connect(at, &AnnealThread::complete, this, &MainWindow::receiveAnnealComplete);
    connect(this, &MainWindow::destroyed, this, &MainWindow::dealClose);
    cThread->start();
    aThread->start();
    initPath();
}

void MainWindow::dealClose(){
    cThread->quit();
    cThread->wait();
    aThread->quit();
    aThread->wait();
    delete ct;
    delete at;
    delete aThread;
    delete cThread;
}

void MainWindow::initPath(){
}

void MainWindow::paintEvent(QPaintEvent *){

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintClimbWidget(){
    ui->climb_length->setText(QString::number(h->curr_length));
    ui->climb_iter->setText(QString::number(h->iter));
    QPainter painter(ui->climb_widget);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    for(int i = 0; i < N; ++i){
        double x = h->cities[i][0] * 411 / 700, y = h->cities[i][1] * 361 / 700;
        painter.drawRoundRect(QRectF(x, y, 3, 3), 2, 2);
    }
    for(int i = 0; i < N - 1; ++i){
        painter.drawLine(QLineF(h->cities[h->path[i]][0] * 411 / 700,
                h->cities[h->path[i]][1] * 361 / 700,
                h->cities[h->path[i + 1]][0] * 411 / 700,
                h->cities[h->path[i + 1]][1] * 361 / 700));
    }
}

void MainWindow::paintAnnealWidget(){
    ui->anneal_length->setText(QString::number(ann->curr_length));
    ui->anneal_t->setText(QString::number(ann->curr_t));
    QPainter painter(ui->anneal_widget);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    for(int i = 0; i < N; ++i){
        double x = ann->cities[i][0] * 411 / 700, y = ann->cities[i][1] * 361 / 700;
        painter.drawRoundRect(QRectF(x, y, 3, 3), 2, 2);
    }
    for(int i = 0; i < N - 1; ++i){
        painter.drawLine(QLineF(ann->cities[ann->path[i]][0] * 411 / 700,
                ann->cities[ann->path[i]][1] * 361 / 700,
                ann->cities[ann->path[i + 1]][0] * 411 / 700,
                ann->cities[ann->path[i + 1]][1] * 361 / 700));
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event){
    if(watched == ui->climb_widget && event->type() == QEvent::Paint){
        paintClimbWidget();
    }
    if(watched == ui->anneal_widget && event->type() == QEvent::Paint){
        paintAnnealWidget();
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::receiveClimbComplete(){
    ui->climb_widget->repaint();
    climb_finished = true;
    if(climb_finished && anneal_finished){
        ui->start->setEnabled(true);
    }
}

void MainWindow::receiveClimbing(){
    ui->climb_widget->repaint();
}

void MainWindow::receiveAnnealing(){
   ui->anneal_widget->repaint();
}

void MainWindow::receiveAnnealComplete(){
    ui->anneal_widget->repaint();
    anneal_finished = true;
    if(climb_finished && anneal_finished){
        ui->start->setEnabled(true);
    }
}


void MainWindow::on_start_clicked()
{
    climb_finished = false;
    anneal_finished = false;
    h->original();
    ann->original();
    emit startClimb();
    emit startAnneal();
    ui->start->setEnabled(false);
}


void MainWindow::on_reset_clicked()
{
    h->original();
    ann->original();
    ui->climb_widget->repaint();
    ui->anneal_widget->repaint();
}

void MainWindow::on_shortest_path_clicked()
{

}
