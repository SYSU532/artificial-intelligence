//
// Created by Miguel Chan on 2018/12/18.
//

#include <iostream>
#include "CImgMNistData.h"
#include "testUtils.h"
#include "NeuralNetwork.h"
#include <vector>
#include <random>
#include <string>
#include <cstring>

using namespace std;

const char* dataPath = "../mnist/network.txt";

int main(int argc, char** argv) {
    bool test = false, isPhoto = false;
    int trainSize = -1;
    string filename;
    if (argc >= 2 ) {
        if (strcmp(argv[1], "test") == 0) {
            test = true;
        } else {
            trainSize = atoi(argv[1]);
        }
    }
    auto data = CImgMNistData::getInstance();
    if (!test) {
        cout << "start training..." << endl;

        vector<int> initSize = {784, 80, 10};
        NeuralNetwork network(initSize);

        auto trainData = data->getTrainSet();
        auto trainLabels = data->getTrainBinaryLabels();

        random_shuffle(begin(trainData), end(trainData));

        if (trainSize != -1) {
            trainData = vector<vector<unsigned char>>(begin(trainData), begin(trainData) +
                    trainSize);
            trainLabels = vector<array<unsigned char, 10>>(begin(trainLabels), begin(trainLabels) +
                                                                        trainSize);
        }

        network.train(trainData, trainLabels, 10, 0.001);

        network.save(dataPath);

    } else {
        NeuralNetwork network(dataPath);
        if (filename.empty()) {

            int size = data->getTestSize(), correct = 0;
            for (int i = 0; i < size; i++) {
                auto tester = data->getTestImageData(i);

                int result = testImage(tester, network);

                cout << "Predict: " << result << " Label: " << data->getTestLabel(i) << endl;

                if (result == data->getTestLabel(i)) {
                    correct++;
                }
            }
            cout << "Correct rate: " << (double) correct / size * 100 << "%" << endl;
        }
    }

    return 0;
}