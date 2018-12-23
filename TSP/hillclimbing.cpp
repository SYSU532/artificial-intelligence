#include "hillclimbing.h"
HillClimbing *HillClimbing::hill = nullptr;
HillClimbing::HillClimbing(){
    int i = 0;
    ifstream input;
    input.open("cities.txt");
    if(input.is_open()){
        while(i < N){
            double node, x, y;
            input >> node >> x >> y;
            cities[i][0] = x;
            cities[i][1] = y;
            path[i] = i;
            ++i;
        }
    }
    else{
        cout << "Can't open cities.txt" << endl;
    }
    input.close();
    curr_length = getDistance();
    ori_length = curr_length;
}

double HillClimbing::getDistance(){
    double length = 0;
    for(int i = 0; i < N - 1; ++i){
        length += sqrt((cities[path[i]][0] - cities[path[i+1]][0]) * (cities[path[i]][0] - cities[path[i+1]][0]) +
        (cities[path[i]][1] - cities[path[i+1]][1]) * (cities[path[i]][1] - cities[path[i+1]][1]));
    }
    length += sqrt((cities[path[0]][0] - cities[path[N-1]][0]) * (cities[path[0]][0] - cities[path[N-1]][0]) +
            (cities[path[0]][1] - cities[path[N-1]][1]) * (cities[path[0]][1] - cities[path[N-1]][1]));
    return length;
}

void HillClimbing::output(){
    ofstream output;
    output.open("path.txt");
    if(output.is_open()){
        for(int i = 0; i < N; ++i){
            output << path[i] + 1 << endl;
        }
        output.close();
    }
    else{
        cout << "Can't open path.txt" << endl;
    }
}

void HillClimbing::original(){
    for(int i = 0; i < N; ++i){
        path[i] = i;
    }
    curr_length = ori_length;
    iter = 0;
}

void HillClimbing::reverse(int x, int y){
    while(x > y){
        int temp = path[x];
        path[x] = path[y];
        path[y] = temp;
        x--;
        y++;
    }
}

double HillClimbing::startClimbing(){
    int x = 0, y = 0;
    while(x == y){
        x = rand_pick();
        y = rand_pick();
    }

    reverse(x, y);
    double new_length = getDistance();
    if(new_length < curr_length){
        return new_length;
    }
    else{
        reverse(x, y);
    }
    return curr_length;
}
