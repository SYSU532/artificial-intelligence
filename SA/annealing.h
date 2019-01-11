#ifndef ANNEALING_HPP
#define ANNEALING_HPP
#include "util.h"


class Annealing{
private:
    static Annealing *ann;
    Annealing();
public:
    double curr_length = 0;
    double ori_length = 0;
    double cities[N][2] = {{0}};
    int path[N] = {0};
    static Annealing* getInstance(){
        if(ann == nullptr){
            ann = new Annealing();
        }
        return ann;
    }
    double curr_t = T0;
    double getDistance();
    double startAnnealing(double);
    void output();
    void reverse(int, int);
    void original();
};

#endif // ANNEALING_H
