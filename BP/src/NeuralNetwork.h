//
// Created by Miguel Chan on 2018/12/18.
//

#ifndef BP_NEURALNETWORK_H
#define BP_NEURALNETWORK_H

#include <vector>
#include <array>
#include "CImg.h"

using namespace cimg_library;

class NeuralNetwork {
private:
    int layers;
    std::vector<int> sizes;

    std::vector<std::vector<double>> biases;

    //Use to fast init a zero temp variable.
    std::vector<std::vector<double>> zeroBiases;
    std::vector<CImg<double>> zeroWeights;

    //We use a CImg object as a matrix in here
    std::vector<CImg<double>> weights;

    void updateWithMiniBatch(const std::vector<std::vector<unsigned char>> &data,
                             const std::vector<std::array<unsigned char, 10>> &labels,
                             double eta);


public:
    explicit NeuralNetwork(std::vector<int> sizes);

    explicit NeuralNetwork(const char *filename);

    void train(const std::vector<std::vector<unsigned char>> &data,
               const std::vector<std::array<unsigned char, 10>> &labels,
               int iterations, double eta);

    void backPropagate(const std::vector<unsigned char> &data,
                       const std::array<unsigned char, 10> &label,
                       std::vector<std::vector<double>> &deltaBiases,
                       std::vector<CImg<double>> &deltaWeights);

    void save(const char *filename);

    std::array<double, 10> predict(std::vector<unsigned char> testData);

};


#endif //BP_NEURALNETWORK_H
