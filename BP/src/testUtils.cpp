//
// Created by Miguel Chan on 2018/12/18.
//

#include <iostream>
#include "testUtils.h"

using namespace std;

std::vector<unsigned char> cimgToData(const CImg<unsigned char> &img) {
    vector<unsigned char> result;
    result.reserve(img.width() * img.height());

    cimg_forY(img, y) {
        cimg_forX(img, x) {
            result.push_back(img(x, y));
        }
    }
    return result;
}

CImg<unsigned char> dataToCImg(const std::vector<unsigned char> &img) {
    CImg<unsigned char> result(28, 28);
    for (int i = 0; i < img.size(); i++) {
        result(i % 28, i / 28) = img[i];
    }
    return result;
}

int testImage(const vector<unsigned char> &imgData, NeuralNetwork &network) {


    auto res = network.predict(imgData);
    int result = -1;
    double max = -1;
    for (int i = 0; i < 10; i++) {
        cout << i << ": " << res[i] << " ";
        if (res[i] > max) {
            max = res[i];
            result = i;
        }
    }
    cout << endl;
    return result;
}
