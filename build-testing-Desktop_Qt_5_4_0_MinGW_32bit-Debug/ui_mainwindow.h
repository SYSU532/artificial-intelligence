/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QPushButton *start;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QLabel *climb_length;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QLabel *climb_iter;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLabel *anneal_length;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QLabel *anneal_t;
    QPushButton *shortest_path;
    QLabel *label_11;
    QPushButton *reset;
    QWidget *climb_widget;
    QWidget *anneal_widget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(956, 590);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));
        start->setGeometry(QRect(430, 430, 101, 28));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 430, 301, 91));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_9);

        climb_length = new QLabel(verticalLayoutWidget);
        climb_length->setObjectName(QStringLiteral("climb_length"));

        horizontalLayout_5->addWidget(climb_length);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_10);

        climb_iter = new QLabel(verticalLayoutWidget);
        climb_iter->setObjectName(QStringLiteral("climb_iter"));

        horizontalLayout_6->addWidget(climb_iter);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(580, 430, 301, 91));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_7);

        anneal_length = new QLabel(verticalLayoutWidget_2);
        anneal_length->setObjectName(QStringLiteral("anneal_length"));

        horizontalLayout_3->addWidget(anneal_length);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_8);

        anneal_t = new QLabel(verticalLayoutWidget_2);
        anneal_t->setObjectName(QStringLiteral("anneal_t"));

        horizontalLayout_4->addWidget(anneal_t);


        verticalLayout_2->addLayout(horizontalLayout_4);

        shortest_path = new QPushButton(centralWidget);
        shortest_path->setObjectName(QStringLiteral("shortest_path"));
        shortest_path->setGeometry(QRect(410, 460, 93, 28));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(520, 460, 51, 31));
        reset = new QPushButton(centralWidget);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setGeometry(QRect(430, 490, 101, 28));
        climb_widget = new QWidget(centralWidget);
        climb_widget->setObjectName(QStringLiteral("climb_widget"));
        climb_widget->setGeometry(QRect(40, 40, 411, 361));
        anneal_widget = new QWidget(centralWidget);
        anneal_widget->setObjectName(QStringLiteral("anneal_widget"));
        anneal_widget->setGeometry(QRect(510, 40, 411, 361));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_2->setText(QApplication::translate("MainWindow", "\347\210\254\345\261\261\346\263\225", 0));
        action_3->setText(QApplication::translate("MainWindow", "\346\250\241\346\213\237\351\200\200\347\201\253\346\263\225", 0));
        start->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", 0));
        label->setText(QApplication::translate("MainWindow", "\347\210\254\345\261\261\346\263\225", 0));
        label_9->setText(QApplication::translate("MainWindow", "\350\267\257\345\276\204\351\225\277\345\272\246\357\274\232", 0));
        climb_length->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "\350\277\255\344\273\243\346\254\241\346\225\260\357\274\232", 0));
        climb_iter->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "\346\250\241\346\213\237\351\200\200\347\201\253\346\263\225", 0));
        label_7->setText(QApplication::translate("MainWindow", "\350\267\257\345\276\204\351\225\277\345\272\246\357\274\232", 0));
        anneal_length->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246\357\274\232", 0));
        anneal_t->setText(QString());
        shortest_path->setText(QApplication::translate("MainWindow", "\346\234\200\347\237\255\350\267\257\345\276\204\357\274\232", 0));
        label_11->setText(QApplication::translate("MainWindow", "6110", 0));
        reset->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
