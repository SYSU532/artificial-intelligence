//
// Created by Miguel Chan on 2018/12/18.
//

#ifndef BP_TESTUTILS_H
#define BP_TESTUTILS_H
#include "CImg.h"
#include "NeuralNetwork.h"
#include <vector>

using namespace cimg_library;

std::vector<unsigned char> cimgToData(const CImg<unsigned char> &img);

CImg<unsigned char> dataToCImg(const std::vector<unsigned char> &img);

int testImage(const std::vector<unsigned char> &imgData, NeuralNetwork &network);

#endif //BP_TESTUTILS_H
