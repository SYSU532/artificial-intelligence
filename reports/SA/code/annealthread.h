#ifndef ANNEALTHREAD_HPP
#define ANNEALTHREAD_HPP
#include <QObject>
#include <QThread>
#include <QImage>
#include <QElapsedTimer>
#include "annealing.h"
class AnnealThread : public QObject
{
    Q_OBJECT
public:
    explicit AnnealThread(QObject *parent = nullptr);
    //线程处理函数,这个线程里面进行绘画图形
    void run();

signals:
    //画图信号
    void running();
    //画图完毕信号
    void complete();

public slots:
};

#endif //
