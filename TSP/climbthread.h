#ifndef CLIMBTHREAD_HPP
#define CLIMBTHREAD_HPP
#include <QObject>
#include <QThread>
#include <QImage>
#include <QElapsedTimer>

class ClimbThread : public QObject
{
    Q_OBJECT
public:
    explicit ClimbThread(QObject *parent = nullptr);

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

