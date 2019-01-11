
#include "annealthread.h"
AnnealThread::AnnealThread(QObject *parent) : QObject(parent)
{

}

void AnnealThread::run()
{
    Annealing *ann = Annealing::getInstance();
    double T = T0;
    double flag = 3900;
    double length = 0;
    while(T > T_min){
        for(int i = 0; i < A_ITER; ++i){
            length = ann->startAnnealing(T);
            ann->curr_length = length;
        }
        ann->curr_t = T;
        T *= ANN_PARAM;
        if(T < flag){
            emit running();
            QElapsedTimer t;
            t.start();
            while(t.elapsed() < 200);
            flag -= 100;
        }
    }
    emit complete();
    ann->output();
}
