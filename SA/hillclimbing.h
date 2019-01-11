#ifndef HILLCLIMBING_HPP
#define HILLCLIMBING_HPP
#include "util.h"

class HillClimbing{
private:
    static HillClimbing *hill;
    HillClimbing();
public:
    static HillClimbing* getInstance(){
        if(hill == nullptr){
            hill = new HillClimbing();
        }
        return hill;
    }
    int iter = 0;
    double curr_length = 0;
    double ori_length = 0;
    double cities[N][2] =  {{0}};
    int path[N] = {0};
    double getDistance();
    void output();
    double startClimbing();
    void reverse(int, int);
    void original();
};



#endif // HILLCLIMBING_H
