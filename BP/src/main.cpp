//
// Created by Miguel Chan on 2018/12/18.
//

#include <iostream>
#include "mnistData.h"
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
    auto data = mnistData::getInstance();
    if (!test) {
        cout << "start training..." << endl;

        vector<int> initSize = {784, 30, 10};
        NeuralNetwork network(initSize);

        auto trainData = data->getTrainSet();
        auto trainLabels = data->getTrainBinaryLabels();

        network.train(trainData, trainLabels, 10000, 0.05);

        network.save(dataPath);
    } else {
        NeuralNetwork network(dataPath);
        if (filename.empty()) {

            int size = data->getTestSize();
            for (int i = 0; i < size; i++) {
                auto tester = data->getTestImageData(i);
                cout << data->getTestLabel(i) << endl;

                auto res = network.predict(tester);
                auto labels = data->getTestBinaryLabels();
                for (int i = 0; i < 10; i++) {
                    cout << i << ": " << res[i] << " ";
                }
                cout << endl;
                dataToCImg(tester).display();
            }
        }
    }

    return 0;
}