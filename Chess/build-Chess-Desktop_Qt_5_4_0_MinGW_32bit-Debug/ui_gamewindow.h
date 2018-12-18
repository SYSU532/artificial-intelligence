/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QPushButton *redRook1;
    QPushButton *redHorse1;
    QPushButton *redElephant1;
    QPushButton *redGuard1;
    QPushButton *redGeneral;
    QPushButton *redSolider1;
    QPushButton *redCannon1;
    QPushButton *redGuard2;
    QPushButton *redElephant2;
    QPushButton *redHorse2;
    QPushButton *redRook2;
    QPushButton *redCannon2;
    QPushButton *redSolider2;
    QPushButton *redSolider3;
    QPushButton *redSolider4;
    QPushButton *redSolider5;
    QPushButton *blackSolider1;
    QPushButton *blackGeneral;
    QPushButton *blackElephant1;
    QPushButton *blackGuard1;
    QPushButton *blackRook1;
    QPushButton *blackHorse1;
    QPushButton *blackCannon1;
    QPushButton *blackSolider2;
    QPushButton *blackSolider3;
    QPushButton *blackSolider4;
    QPushButton *blackSolider5;
    QPushButton *blackCannon2;
    QPushButton *blackGuard2;
    QPushButton *blackElephant2;
    QPushButton *blackHorse2;
    QPushButton *blackRook2;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(521, 578);
        GameWindow->setStyleSheet(QStringLiteral("background-image:url(:/Sample/images/WOOD.GIF)"));
        redRook1 = new QPushButton(GameWindow);
        redRook1->setObjectName(QStringLiteral("redRook1"));
        redRook1->setGeometry(QRect(0, 520, 57, 57));
        redRook1->setStyleSheet(QStringLiteral("background-image:url(:/Sample/images/WOOD/RR.GIF);border-radius:50%;height:20px;width:20px;"));
        redHorse1 = new QPushButton(GameWindow);
        redHorse1->setObjectName(QStringLiteral("redHorse1"));
        redHorse1->setGeometry(QRect(60, 520, 57, 57));
        redHorse1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RN.GIF);border-radius:50%;height:20px;width:20px;"));
        redElephant1 = new QPushButton(GameWindow);
        redElephant1->setObjectName(QStringLiteral("redElephant1"));
        redElephant1->setGeometry(QRect(120, 520, 57, 57));
        redElephant1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RB.GIF);border-radius:50%;height:20px;width:20px;"));
        redGuard1 = new QPushButton(GameWindow);
        redGuard1->setObjectName(QStringLiteral("redGuard1"));
        redGuard1->setGeometry(QRect(178, 520, 57, 57));
        redGuard1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RA.GIF);border-radius:50%;"));
        redGeneral = new QPushButton(GameWindow);
        redGeneral->setObjectName(QStringLiteral("redGeneral"));
        redGeneral->setGeometry(QRect(235, 520, 57, 57));
        redGeneral->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RK.GIF);border-radius:50%;height:20px;width:20px;"));
        redSolider1 = new QPushButton(GameWindow);
        redSolider1->setObjectName(QStringLiteral("redSolider1"));
        redSolider1->setGeometry(QRect(0, 340, 57, 57));
        redSolider1->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/RP.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        redCannon1 = new QPushButton(GameWindow);
        redCannon1->setObjectName(QStringLiteral("redCannon1"));
        redCannon1->setGeometry(QRect(60, 400, 57, 57));
        redCannon1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RC.GIF);border-radius:50%;height:20px;width:20px;"));
        redGuard2 = new QPushButton(GameWindow);
        redGuard2->setObjectName(QStringLiteral("redGuard2"));
        redGuard2->setGeometry(QRect(292, 520, 57, 57));
        redGuard2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RA.GIF);border-radius:50%;height:20px;width:20px;"));
        redElephant2 = new QPushButton(GameWindow);
        redElephant2->setObjectName(QStringLiteral("redElephant2"));
        redElephant2->setGeometry(QRect(350, 520, 57, 57));
        redElephant2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RB.GIF);border-radius:50%;height:20px;width:20px;"));
        redHorse2 = new QPushButton(GameWindow);
        redHorse2->setObjectName(QStringLiteral("redHorse2"));
        redHorse2->setGeometry(QRect(408, 520, 57, 57));
        redHorse2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RN.GIF);border-radius:50%;height:20px;width:20px;"));
        redRook2 = new QPushButton(GameWindow);
        redRook2->setObjectName(QStringLiteral("redRook2"));
        redRook2->setGeometry(QRect(465, 520, 57, 57));
        redRook2->setStyleSheet(QStringLiteral("background-image:url(:/Sample/images/WOOD/RR.GIF);border-radius:50%;height:20px;width:20px;"));
        redCannon2 = new QPushButton(GameWindow);
        redCannon2->setObjectName(QStringLiteral("redCannon2"));
        redCannon2->setGeometry(QRect(408, 400, 57, 57));
        redCannon2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/RC.GIF);border-radius:50%;height:20px;width:20px;"));
        redSolider2 = new QPushButton(GameWindow);
        redSolider2->setObjectName(QStringLiteral("redSolider2"));
        redSolider2->setGeometry(QRect(120, 340, 57, 57));
        redSolider2->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/RP.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        redSolider3 = new QPushButton(GameWindow);
        redSolider3->setObjectName(QStringLiteral("redSolider3"));
        redSolider3->setGeometry(QRect(232, 340, 57, 57));
        redSolider3->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/RP.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        redSolider4 = new QPushButton(GameWindow);
        redSolider4->setObjectName(QStringLiteral("redSolider4"));
        redSolider4->setGeometry(QRect(348, 340, 57, 57));
        redSolider4->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/RP.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        redSolider5 = new QPushButton(GameWindow);
        redSolider5->setObjectName(QStringLiteral("redSolider5"));
        redSolider5->setGeometry(QRect(460, 340, 57, 57));
        redSolider5->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/RP.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        blackSolider1 = new QPushButton(GameWindow);
        blackSolider1->setObjectName(QStringLiteral("blackSolider1"));
        blackSolider1->setGeometry(QRect(0, 170, 58, 58));
        blackSolider1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BP.GIF);border-radius:50%;height:20px;width:20px;"));
        blackGeneral = new QPushButton(GameWindow);
        blackGeneral->setObjectName(QStringLiteral("blackGeneral"));
        blackGeneral->setGeometry(QRect(235, 0, 58, 58));
        blackGeneral->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BK.GIF);border-radius:50%;height:20px;width:20px;"));
        blackElephant1 = new QPushButton(GameWindow);
        blackElephant1->setObjectName(QStringLiteral("blackElephant1"));
        blackElephant1->setGeometry(QRect(120, 0, 58, 58));
        blackElephant1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BB.GIF);border-radius:50%;height:20px;width:20px;"));
        blackGuard1 = new QPushButton(GameWindow);
        blackGuard1->setObjectName(QStringLiteral("blackGuard1"));
        blackGuard1->setGeometry(QRect(178, 0, 58, 58));
        blackGuard1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BA.GIF);border-radius:50%;height:20px;width:20px;"));
        blackRook1 = new QPushButton(GameWindow);
        blackRook1->setObjectName(QStringLiteral("blackRook1"));
        blackRook1->setGeometry(QRect(0, 0, 58, 58));
        blackRook1->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/BR.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        blackHorse1 = new QPushButton(GameWindow);
        blackHorse1->setObjectName(QStringLiteral("blackHorse1"));
        blackHorse1->setGeometry(QRect(60, 0, 58, 58));
        blackHorse1->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BN.GIF);border-radius:50%;height:20px;width:20px;"));
        blackCannon1 = new QPushButton(GameWindow);
        blackCannon1->setObjectName(QStringLiteral("blackCannon1"));
        blackCannon1->setGeometry(QRect(60, 120, 58, 58));
        blackCannon1->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/BC.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        blackSolider2 = new QPushButton(GameWindow);
        blackSolider2->setObjectName(QStringLiteral("blackSolider2"));
        blackSolider2->setGeometry(QRect(120, 170, 58, 58));
        blackSolider2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BP.GIF);border-radius:50%;height:20px;width:20px;"));
        blackSolider3 = new QPushButton(GameWindow);
        blackSolider3->setObjectName(QStringLiteral("blackSolider3"));
        blackSolider3->setGeometry(QRect(232, 170, 58, 58));
        blackSolider3->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BP.GIF);border-radius:50%;height:20px;width:20px;"));
        blackSolider4 = new QPushButton(GameWindow);
        blackSolider4->setObjectName(QStringLiteral("blackSolider4"));
        blackSolider4->setGeometry(QRect(348, 170, 58, 58));
        blackSolider4->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BP.GIF);border-radius:50%;height:20px;width:20px;"));
        blackSolider5 = new QPushButton(GameWindow);
        blackSolider5->setObjectName(QStringLiteral("blackSolider5"));
        blackSolider5->setGeometry(QRect(460, 170, 58, 58));
        blackSolider5->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BP.GIF);border-radius:50%;height:20px;width:20px;"));
        blackCannon2 = new QPushButton(GameWindow);
        blackCannon2->setObjectName(QStringLiteral("blackCannon2"));
        blackCannon2->setGeometry(QRect(408, 120, 58, 58));
        blackCannon2->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/BC.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        blackGuard2 = new QPushButton(GameWindow);
        blackGuard2->setObjectName(QStringLiteral("blackGuard2"));
        blackGuard2->setGeometry(QRect(290, 0, 58, 58));
        blackGuard2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BA.GIF);border-radius:50%;height:20px;width:20px;"));
        blackElephant2 = new QPushButton(GameWindow);
        blackElephant2->setObjectName(QStringLiteral("blackElephant2"));
        blackElephant2->setGeometry(QRect(350, 0, 58, 58));
        blackElephant2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BB.GIF);border-radius:50%;height:20px;width:20px;"));
        blackHorse2 = new QPushButton(GameWindow);
        blackHorse2->setObjectName(QStringLiteral("blackHorse2"));
        blackHorse2->setGeometry(QRect(408, 0, 58, 58));
        blackHorse2->setStyleSheet(QStringLiteral("background-image: url(:/Sample/images/WOOD/BN.GIF);border-radius:50%;height:20px;width:20px;"));
        blackRook2 = new QPushButton(GameWindow);
        blackRook2->setObjectName(QStringLiteral("blackRook2"));
        blackRook2->setGeometry(QRect(465, 0, 58, 58));
        blackRook2->setStyleSheet(QLatin1String("background-image: url(:/Sample/images/WOOD/BR.GIF);border-radius:50%;height:20px;width:20px;\n"
""));
        graphicsView = new QGraphicsView(GameWindow);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(520, 0, 111, 571));
        graphicsView->setStyleSheet(QStringLiteral("background-image: url(:/red.jpg);"));
        graphicsView_2 = new QGraphicsView(GameWindow);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(630, 0, 101, 571));
        graphicsView_2->setStyleSheet(QStringLiteral("background-image: url(:/red.jpg);"));

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Form", 0));
        redRook1->setText(QString());
        redHorse1->setText(QString());
        redElephant1->setText(QString());
        redGuard1->setText(QString());
        redGeneral->setText(QString());
        redSolider1->setText(QString());
        redCannon1->setText(QString());
        redGuard2->setText(QString());
        redElephant2->setText(QString());
        redHorse2->setText(QString());
        redRook2->setText(QString());
        redCannon2->setText(QString());
        redSolider2->setText(QString());
        redSolider3->setText(QString());
        redSolider4->setText(QString());
        redSolider5->setText(QString());
        blackSolider1->setText(QString());
        blackGeneral->setText(QString());
        blackElephant1->setText(QString());
        blackGuard1->setText(QString());
        blackRook1->setText(QString());
        blackHorse1->setText(QString());
        blackCannon1->setText(QString());
        blackSolider2->setText(QString());
        blackSolider3->setText(QString());
        blackSolider4->setText(QString());
        blackSolider5->setText(QString());
        blackCannon2->setText(QString());
        blackGuard2->setText(QString());
        blackElephant2->setText(QString());
        blackHorse2->setText(QString());
        blackRook2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
