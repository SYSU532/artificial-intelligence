//
// Created by Miguel Chan on 2018/12/18.
//

#include "NeuralNetwork.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

NeuralNetwork::NeuralNetwork(std::vector<int> sizes) {
    layers = static_cast<int>(sizes.size());
    this->sizes = sizes;
    default_random_engine generator;
    normal_distribution<double> nDist;
    biases.reserve(layers-1);
    zeroBiases.reserve(layers-1);
    //Generate biases, the first layer has no biases.
    for (int i = 1; i < layers; i++) {
        vector<double> tempBias;
        tempBias.reserve(sizes[i]);
        for (int k = 0; k < sizes[i]; k++) {
            double bias = nDist(generator);
            tempBias.push_back(bias);
        }
        biases.push_back(tempBias);
        zeroBiases.push_back(vector<double>(sizes[i], 0));
    }

    //Generate weights
    weights.reserve(static_cast<unsigned long>(layers - 1));
    zeroWeights.reserve(static_cast<unsigned long>(layers - 1));
    for (int i = 0; i < layers - 1; i++) {
        int curr = sizes[i], next = sizes[i + 1];
        CImg<double> temp(curr, next);
        cimg_forXY(temp, x, y) {
                temp(x, y) = nDist(generator);
            }
        weights.push_back(temp);
        zeroWeights.emplace_back(curr, next, 1, 1, 0);
    }
}

//Load a neural network from saved file
NeuralNetwork::NeuralNetwork(const char *filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Fail to open the file to load the neural network");
    }
    file >> layers;
    sizes.reserve(layers);
    for (int i = 0; i < layers; i++) {
        int size;
        file >> size;
        sizes.push_back(size);
    }
    biases.reserve(layers-1);
    zeroBiases.reserve(layers-1);
    for (int i = 1; i < layers; i++) {
        vector<double> temp;
        temp.reserve(sizes[i]);
        for (int k = 0; k < sizes[i]; k++) {
            double bias;
            file >> bias;
            temp.push_back(bias);
        }
        biases.push_back(temp);
        zeroBiases.emplace_back(sizes[i], 0);
    }

    weights.reserve(layers - 1);
    zeroWeights.reserve(static_cast<unsigned long>(layers - 1));
    for (int i = 0; i < layers - 1; i++) {
        int curr = sizes[i], next = sizes[i + 1];
        CImg<double> temp(curr, next);
        cimg_forXY(temp, x, y) {
                double w;
                file >> w;
                temp(x, y) = w;
            }
        weights.push_back(temp);
        zeroWeights.emplace_back(curr, next, 1, 1, 0);
    }
}

//Serialize the network and save to a file
void NeuralNetwork::save(const char *filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Fail to open the file to save the neural network");
    }
    file << layers << " ";
    for (int i = 0; i < sizes.size(); i++) {
        file << sizes[i] << " ";
    }
    for (int i = 0; i < biases.size(); i++) {
        for (int k = 0; k < biases[i].size(); k++) {
            file << biases[i][k] << " ";
        }
    }
    for (int i = 0; i < weights.size(); i++) {
        cimg_forXY(weights[i], x, y) {
                file << weights[i](x, y) << " ";
            }
    }
    file << endl;
}

//eta is the learning rate
void NeuralNetwork::train(const std::vector<std::vector<unsigned char>> &data,
                          const std::vector<std::array<unsigned char, 10>> &labels,
                          int iterations, double eta) {
    assert(data.size() == labels.size());
    assert(data.size() % miniBatchSize == 0);
    int n = static_cast<int>(data.size());
    //t is the iterations count
    int t = n / miniBatchSize;

    for (int i = 0; i < t; i++) {
        int startIndex = i * miniBatchSize, endIndex = (i + 1) * miniBatchSize;
        std::vector<std::vector<unsigned char>> miniBatch(begin(data) + startIndex,
                                                          begin(data) + endIndex);
        std::vector<std::array<unsigned char, 10>> miniLabels(begin(labels) + startIndex,
                                                              begin(labels) + endIndex);
        for (int k = 0; k < 10; k++) {
            updateWithMiniBatch(miniBatch, miniLabels, eta);
            cout << "\r Current Trained: " << (double)k / 10 * 100 << "%." << flush;
        }
        cout << "\r                                      ";
        cout << "\rTrained " << i << " batch(es), " << t - i - 1 << " to go." << endl;
    }

}

CImg<double> dotProduct(const CImg<double> &a, const CImg<double>& b) {
    assert(a.width() == b.height());
    CImg<double> result(b.width(), a.height(), 1, 1, 0);
    for (int i = 0; i < a.height(); i++) {
        for (int k = 0; k < a.width(); k++) {
            double r = a(k, i);
            for (int j = 0; j < b.width(); j++) {
                result(j, i) = r * b(j, k);
            }
        }
    }
    return result;
}

//inplace sigmoid
CImg<double> sigmoid(const CImg<double> &input) {
    CImg<double> result(input.width(), input.height(), 1, 1, 0);
    cimg_forXY(input, x, y) {
        result(x, y) = 1 / (1 + exp(-input(x, y)));
    }
    return result;
}

CImg<double> sigmoidPrime(const CImg<double>& input) {
    auto sig = sigmoid(input);
    return sig.mul(-sig + 1);
}

CImg<double> labelsToCImg(const array<unsigned char, 10> &labels) {
    CImg<double> res(1, 10, 1, 1, 0);
    for (int i = 0; i < 10; i++) {
        res(0, i) = labels[i];
    }
    return res;
}


//Update biases and weights
void NeuralNetwork::updateWithMiniBatch(const std::vector<std::vector<unsigned char>> &data,
                                        const std::vector<std::array<unsigned char, 10>> &labels,
                                        double eta) {
    vector<vector<double>> newBiases(zeroBiases);
    vector<CImg<double>> newWeights(zeroWeights);

    for (int i = 0; i < data.size(); i++) {
        vector<vector<double>> deltaBiases;
        vector<CImg<double>> deltaWeights;
        backPropagate(data[i], labels[i], deltaBiases, deltaWeights);
        for (int k = 0; k < biases.size(); k++) {
            for (int j = 0; j < biases[k].size(); j++) {
                newBiases[k][j] += deltaBiases[k][j];
            }
        }
        for (int k = 0; k < deltaWeights.size(); k++) {
            newWeights[k] += deltaWeights[k];
        }
    }
    double rate = eta / data.size();
    for (int i = 0; i < weights.size(); i++) {
        weights[i] -= rate * newWeights[i];
    }
    for (int i = 0; i < biases.size(); i++) {
        for (int k = 0; k < biases[i].size(); k++) {
            biases[i][k] -= rate * newBiases[i][k];
        }
    }

}

void NeuralNetwork::backPropagate(const vector<unsigned char> &data,
                                  const array<unsigned char, 10> &label,
                                  vector<vector<double>> &deltaBiases,
                                  vector<CImg<double>> &deltaWeights) {
    deltaBiases = zeroBiases;
    deltaWeights = zeroWeights;

    auto y = labelsToCImg(label);

    vector<CImg<double>> activations;
    vector<CImg<double>> zs;

    CImg<double> input(1, data.size(), 1, 1, 0);
    for (int i = 0; i < data.size(); i++) {
        input(0, i) = data[i];
    }
    activations.push_back(input);

    for (int i = 0; i < layers - 1; i++) {
        CImg<double> newInput = (weights[i] * input);
        cimg_forX(newInput, x) {
            newInput(x, 1) += biases[i][x];
        }
        zs.push_back(newInput);
        input = sigmoid(newInput);
        activations.push_back(input);
    }

    //Start backward
    auto delta = activations[activations.size() - 1] - y;
    delta.mul(sigmoidPrime(zs[zs.size() - 1]));
    memcpy(deltaBiases[deltaBiases.size() - 1].data(), delta.data(),
           delta.height() * sizeof(double));
    deltaWeights[deltaWeights.size() - 1] = delta * activations[activations.size()-2].get_transpose();
    for (int i = layers - 3; i >= 0; i--) {
        auto z = zs[i];
        auto sp = sigmoidPrime(z);
        delta = (weights[i+1].get_transpose() * delta).get_mul(sp);
        memcpy(deltaBiases[i].data(), delta.data(), delta.height() * sizeof(double));
        deltaWeights[i] = delta * activations[i].get_transpose();
    }
}


std::array<double, 10> NeuralNetwork::predict(std::vector<unsigned char> testData) {
    CImg<double> input(1, testData.size(), 1, 1, 0);
    for (int k = 0; k < testData.size(); k++) {
        input(0, k) = testData[k];
    }
    for (int i = 0; i < layers - 1; i++) {
        input = (weights[i] * input);
        for (int k = 0; k < biases[i].size(); k++) {
            input(0, k) += biases[i][k];
        }
        input = sigmoid(input);
    }
    array<double, 10> result{};
    for (int i = 0; i < input.height(); i++) {
        result[i] = input(0, i);
    }
    return result;
}





