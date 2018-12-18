//
// Created by Miguel Chan on 2018/12/16.
//

#ifndef NUMBER_DETECTION_MNISTDATA_H
#define NUMBER_DETECTION_MNISTDATA_H

#include <memory>
#include <vector>
#include "CImg.h"
#include <array>

using namespace cimg_library;

class mnistData {
private:
    static std::shared_ptr<mnistData> singleton;
    mnistData();
    std::vector<CImg<unsigned char>> trainImg;
    std::vector<CImg<unsigned char>> testImg;
    std::vector<unsigned char> trainLabels;
    std::vector<unsigned char> testLabels;
    std::vector<std::vector<unsigned char>> trainSet;
    std::vector<std::vector<unsigned char>> testSet;
    std::vector<unsigned char> trainLabelMat;
    std::vector<unsigned char> testLabelMat;
    std::vector<std::array<unsigned char, 10>> trainBinaryLabels;
    std::vector<std::array<unsigned char, 10>> testBinaryLabels;

public:
    CImg<unsigned char> getTestImage(int index);
    CImg<unsigned char> getTrainImage(int index);
    std::vector<unsigned char> getTestImageData(int index);
    std::vector<unsigned char> getTrainImageData(int index);
    int getTestLabel(int index);
    int getTrainLabel(int index);
    static std::shared_ptr<mnistData> getInstance();
    std::vector<std::vector<unsigned char>> getTrainSet();
    std::vector<std::vector<unsigned char>> getTestSet();
    std::vector<std::array<unsigned char, 10>> getTrainBinaryLabels();
    std::vector<std::array<unsigned char, 10>> getTestBinaryLabels();
    int getTrainSize();
    int getTestSize();

};


#endif //NUMBER_DETECTION_MNISTDATA_H
