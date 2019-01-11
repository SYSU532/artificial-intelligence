#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>


namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    
    void initActions();

    ~MainWindow();

private slots:
	// Tool functions
    void showMainWindow();
	void start();
	void help();
	void exit();
	
signals:
    void showGameWindow();

private:
    Ui::MainWindow* ui;
    QMediaPlayer *player;

    bool gameStart;
    bool gameOver;

};

#endif // MAINWINDOW_H
