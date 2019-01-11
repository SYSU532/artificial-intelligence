#ifndef UTIL_H
#define UTIL_H
#include <cmath>
#include <ctime>
#include <fstream>
#include <random>
#include <functional>
#include <iostream>

using namespace std;
#define N 130   //number of cities
#define A_ITER 500   //annealing iteration
#define T_min (1e-8)    //ending_temperature
#define T0 4000.0   //init_temperature
#define ANN_PARAM 0.98  //param
#define H_ITER 50000   //hillclimbing iteration

mt19937::result_type static seed = static_cast<unsigned int>(time(nullptr));
auto static rand_pick = bind(std::uniform_int_distribution<int>(0, N-1), mt19937(seed));

#endif // UTIL_H
