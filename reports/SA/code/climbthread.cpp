#include "climbthread.h"
#include "hillclimbing.h"
ClimbThread::ClimbThread(QObject *parent) : QObject(parent)
{

}

void ClimbThread::run()
{
    HillClimbing *h = HillClimbing::getInstance();
    double length = 0;
    int flag = 1000;
    for(int i = 0; i < H_ITER; ++i){
        length = h->startClimbing();
        h->curr_length = length;
        if(i == flag){
            h->iter = i;
            emit running();
            flag += 1000;
            QElapsedTimer t;
            t.start();
            while(t.elapsed() < 200);
        }
    }
    h->iter = H_ITER;
    emit complete();
    h->output();
}

