//
// Created by Miguel Chan on 2018/12/22.
//

#include "NeuralNetworkTest.h"
#include "CImgMNistData.h"
#include "testUtils.h"

double testCorrectRate(NeuralNetwork &network) {
    auto data = CImgMNistData::getInstance();
    int size = data->getTestSize(), correct = 0;
    for (int i = 0; i < size; i++) {
        auto tester = data->getTestImageData(i);

        int result = testImage(tester, network);


        if (result == data->getTestLabel(i)) {
            correct++;
        }
    }
    return (double) correct / size * 100;
}

CImg<unsigned char> drawRateGraph(const std::vector<double> &rates) {
    CImg<unsigned char> result(420, 400, 1, 3, 255);
    unsigned char colorBlue[3] = {0, 0, 255};
    CImg<int> points(rates.size(), 2, 1, 1, 0);

    for (int i = 0; i < rates.size(); i++) {
        result.draw_circle(10 + 400 * i / rates.size(), 400 - rates[i] * 4, 3, colorBlue);
        points(i, 0) = 10 + 400 * i / rates.size();
        points(i, 1) = 400 - rates[i] * 4;
    }
    result.draw_line(points, colorBlue);

    return result;
}
