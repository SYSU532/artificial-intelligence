#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <QString>
#include <cmath>
#include <QSoundEffect>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include "Chess.h"

#define GAP 60.0

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget* parent = 0);

    void initActions();

    void resetBoardChessImg();
    bool isGameOver();
    void setGameOver(bool over);

    ~GameWindow();

protected:
    void mousePressEvent(QMouseEvent* event);

private slots:
    void showGame();
    // Game logic methods
    void aiMove();
    // Chess Board click events
    void clickOnChess(QString a);
    void setButton(int index);
    void blackBtnPress(int index);

signals:
    void GameOver();

private:
    Ui::GameWindow* ui;
    QSoundEffect player;

    chessBoard* board;
    chess clickTarget;
    // Mappers
    QSignalMapper* mapper;
    QSignalMapper* indexMapper;
    QSignalMapper* blackBtnMapper;
    // UI's buttons
    QPushButton* btn[16];
    QPushButton* blackBtn[16];
    QPushButton* button;
    // Tool variables
    QString image[16];
    pair<int, int> targetPos;
    int targetIndex;
    int targetLevel;

    // Play flags
    bool playerSide;
    int turn;

};

#endif // GAMEWINDOW_H
