//
// Created by Miguel Chan on 2018/12/18.
//

#include "NeuralNetwork.h"
#include "NeuralNetworkTest.h"
#include <cmath>
#include <ctime>
#include <assert.h>
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
    for (int i = 0; i < weights.size(); i++) {
        cimg_forXY(weights[i], x, y) {
                file << weights[i](x, y) << " ";
            }
    }
    file << endl;
}

double getError(const CImg<double> &out, const std::array<unsigned char, 10> &label) {
    assert(out.height() == 10 && out.width() == 1);
    double res = 0;
    for (int i = 0; i < 10; i++) {
        double diff = out(0, i) - label[i];
        res += diff * diff;
    }
    return res;
}

//inplace sigmoid
CImg<double> sigmoid(const CImg<double> &input) {
    CImg<double> result(input.width(), input.height(), 1, 1, 0);
    cimg_forXY(input, x, y) {
            result(x, y) = 1 / (1 + exp(-input(x, y)));
        }
    return result;
}


//Derivative of sigmoid
CImg<double> sigmoidPrime(const CImg<double> &input) {
    auto sig = sigmoid(input);
    return sig.mul(-sig + 1);
}

const double thresh = 0.005;

//eta is the learning rate
void NeuralNetwork::train(const std::vector<std::vector<unsigned char>> &data,
                          const std::vector<std::array<unsigned char, 10>> &labels,
                          int iterations, double eta) {
    assert(data.size() == labels.size());
    int n = static_cast<int>(data.size());
    double correctRate = testCorrectRate(*this);
    correctRates.push_back(correctRate);

    for (int i = 0; i < n; i++) {
        for (int t = 0; t < iterations; t++) {
            auto label = labels[i];
            CImg<double> labelData(1, 10, 1, 1, 0);
            for (int k = 0; k < 10; k++) {
                labelData(0, k) = label[k];
            }
            vector<CImg<double>> in, out;
            forward(data[i], in, out);

            CImg<double> input(1, data[i].size(), 1, 1, 0);
            for (int k = 0; k < data[i].size(); k++) {
                input(0, k) = (double)data[i][k] / 255;
            }

            auto error = getError(out[out.size() - 1], label);
            if (error < thresh) break;

            //order is backward in these vectors
            vector<CImg<double>> gradients, deltas;

            gradients.push_back(out[out.size()-1].get_mul(-out[out.size()-1]+1).
                    get_mul(labelData - out[out.size()-1]));

            for (int i = 1; i < layers - 1; i++) {
                auto gradient = sigmoidPrime(in[in.size() - i - 1]);
                gradient += weights[weights.size()-i].get_transpose() * gradients[i-1];
                gradients.push_back(gradient);
            }

            for (int i = 0; i < layers - 1; i++) {
                auto delta = gradients[i] * (out[out.size()-i-2].get_transpose())
                        * eta;
                deltas.push_back(delta);
                weights[weights.size() - 1- i] += delta;
            }

        }

        if ((i + 1) % 1000 == 0) {
            cout << "\r                                            "
                    << "                                           ";
            cout << "\rRecalculating correct rate..." << flush;
            correctRate = testCorrectRate(*this);
            correctRates.push_back(correctRate);
        }

        cout << "\rTrained " << i + 1 << " samples out of a total of "
                                                      << n << " samples. Correct rate: "
                                                              << correctRate << "%."  << flush;
    }
    cout << endl;

    rateGraph = drawRateGraph(correctRates);
}

CImg<double> dotProduct(const CImg<double> &a, const CImg<double> &b) {
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



CImg<double> labelsToCImg(const array<unsigned char, 10> &labels) {
    CImg<double> res(1, 10, 1, 1, 0);
    for (int i = 0; i < 10; i++) {
        res(0, i) = labels[i];
    }
    return res;
}


std::array<double, 10> NeuralNetwork::predict(const std::vector<unsigned char> &testData) {

    CImg<double> input(1, testData.size(), 1, 1, 0);
    for (int k = 0; k < testData.size(); k++) {
        input(0, k) = (double)testData[k] / 255;
    }
    for (int i = 0; i < layers - 1; i++) {
        input = (weights[i] * input);
        input = sigmoid(input);
    }
    array<double, 10> result{};
    for (int i = 0; i < input.height(); i++) {
        result[i] = input(0, i);
    }
    return result;
}

void NeuralNetwork::forward(const std::vector<unsigned char> &testData,
                                                 std::vector<CImg<double>> &inputs,
                                                 std::vector<CImg<double>> &outputs) {

    CImg<double> input(1, testData.size(), 1, 1, 0);
    for (int k = 0; k < testData.size(); k++) {
        input(0, k) = (double)testData[k] / 255;
    }
    outputs.push_back(input);
    for (int i = 0; i < layers - 1; i++) {
        input = (weights[i] * input);
        inputs.push_back(input);
        input = sigmoid(input);
        outputs.push_back(input);
    }
}

CImg<unsigned char> NeuralNetwork::getRateGraph() {
    return rateGraph;
}





