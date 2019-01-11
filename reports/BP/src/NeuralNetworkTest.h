//
// Created by Miguel Chan on 2018/12/22.
//

#ifndef BP_NEURALNETWORKTEST_H
#define BP_NEURALNETWORKTEST_H

#include "NeuralNetwork.h"
#include <vector>

double testCorrectRate(NeuralNetwork& tester);

CImg<unsigned char> drawRateGraph(const std::vector<double>& rates);

#endif //BP_NEURALNETWORKTEST_H
