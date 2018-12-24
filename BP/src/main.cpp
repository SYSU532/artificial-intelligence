//
// Created by Miguel Chan on 2018/12/18.
//

#include <iostream>
#include "CImgMNistData.h"
#include "testUtils.h"
#include "NeuralNetwork.h"
#include "NumberSegmentation.h"
#include <random>
#include <vector>
#include <random>
#include <string>
#include <cstring>

using namespace std;

const char* dataPath = "../mnist/network.txt";
const char* graphPath = "../mnist/rateGraph.bmp";

int main(int argc, char** argv) {
    bool test = false, isPhoto = false;
    int trainSize = -1;
    string filename;
    if (argc >= 2 ) {
        if (strcmp(argv[1], "test") == 0) {
            test = true;
        } else if(strcmp(argv[1], "file") == 0 && argc >= 3) {
            filename = argv[2];
            test = true;
        } else {
            trainSize = atoi(argv[1]);
        }
    }
    auto data = CImgMNistData::getInstance();
    if (!test) {
        cout << "start training..." << endl;

        vector<int> initSize = {784, 30, 10};
        NeuralNetwork network(initSize);

        auto trainData = data->getTrainSet();
        auto trainLabels = data->getTrainBinaryLabels();

        if (trainSize != -1) {
            trainData = vector<vector<unsigned char>>(begin(trainData), begin(trainData) +
                    trainSize);
            trainLabels = vector<array<unsigned char, 10>>(begin(trainLabels), begin(trainLabels) +
                                                                        trainSize);
        }

        network.train(trainData, trainLabels, 30, 0.01);

        network.save(dataPath);

        auto rateGraph = network.getRateGraph();
        rateGraph.save(graphPath);

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
        } else {
            CImg<unsigned char> image(filename.c_str());
            ImageSegmentation ism(image);

            ism.processBinaryImage();
            ism.numberSegmentationMainProcess("../output/");

            int size = ism.getImageCount();
            cout << size << endl;

            string res = "";
            for(int i=0; i<size; i++){
                string path = "../output/" + to_string(i);
                path += ".bmp";
                CImg<unsigned char> img(path.c_str());
                img = toGreyScale(img);
                img.resize(28, 28);
                img.threshold(130);

                vector<unsigned char> imgData(28*28, 0);
                for (int i = 0; i < 28 * 28; i++) {
                    imgData[i] = img(i % 28, i / 28);
                }

                int result = testImage(imgData, network);
                cout << "Predict: " << result << endl;
                res += to_string(result) + " ";
                img.display();
            }
            cout << "Final Result: " << res << endl;
        }
    }

    return 0;
}