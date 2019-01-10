#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "hillclimbing.h"
#include "qpainter.h"
#include "util.h"
#include "annealing.h"
#include "climbthread.h"
#include "annealthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
signals:
    void startClimb();
    void startAnneal();

private slots:
    void on_start_clicked();

    void on_reset_clicked();

private:
    bool climb_finished = false, anneal_finished = false;
    void paintEvent(QPaintEvent *);
    void initPath();
    void paintClimbWidget();
    void paintAnnealWidget();
    bool eventFilter(QObject *, QEvent *);
    void receiveClimbing();
    void receiveAnnealing();
    void receiveClimbComplete();
    void receiveAnnealComplete();
    void dealClose();

    Ui::MainWindow *ui;
    HillClimbing *h;
    Annealing *ann;
    QThread *cThread, *aThread;
    ClimbThread *ct;
    AnnealThread *at;
};

#endif // MAINWINDOW_H
