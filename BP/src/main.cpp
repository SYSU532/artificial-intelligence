//
// Created by Miguel Chan on 2018/12/18.
//

#include <iostream>
#include "CImgMNistData.h"
#include "testUtils.h"
#include "NeuralNetwork.h"
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const char* dataPath = "../mnist/network.txt";

int main(int argc, char** argv) {
    bool test = false, isPhoto = false;
    string filename;
    if (argc >= 2 && strcmp(argv[1], "test") == 0) {
        test = true;
    }
    auto data = CImgMNistData::getInstance();
    if (!test) {
        cout << "start training..." << endl;

        vector<int> initSize = {784, 100, 40, 10};
        NeuralNetwork network(initSize);

        auto trainData = data->getTrainSet();
        auto trainLabels = data->getTrainBinaryLabels();

        network.train(trainData, trainLabels, 20, 0.01);

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