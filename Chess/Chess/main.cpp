#include "mainwindow.h"
#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameWindow g;
    w.show();

    QObject::connect(&w, SIGNAL(showGameWindow()), &g, SLOT(showGame()));
    QObject::connect(&g, SIGNAL(GameOver()), &w, SLOT(showMainWindow()));

    return a.exec();
}
