//
// Created by Miguel Chan on 2018/12/16.
//

#include "CImgMNistData.h"
#include <cstdlib>
#include <array>
#include <fstream>
#include <iostream>

using namespace std;

shared_ptr<CImgMNistData> CImgMNistData::singleton = nullptr;

const char* trainImagePath = "./../mnist/train-images-idx3-ubyte";
const char* testImagePath = "./../mnist/t10k-images-idx3-ubyte";
const char* trainLabelPath = "./../mnist/train-labels-idx1-ubyte";
const char* testLabelPath = "./../mnist/t10k-labels-idx1-ubyte";

std::shared_ptr<CImgMNistData> CImgMNistData::getInstance() {
    if (singleton == nullptr) {
        singleton = shared_ptr<CImgMNistData>(new CImgMNistData);
    }
    return singleton;
}

void checkFileStatus(ifstream& file, const string &filename) {
    if (!file.is_open()) {
        cerr << "Cannot open file " << filename << endl;
        exit(1);
    }
}

int reverseInt(int i) {
    unsigned char c1, c2, c3, c4;
    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}


void readImgFile(ifstream& imgFile, vector<CImg<unsigned char>>& imgList, std::vector<std::vector<unsigned char>>& imgSet) {
    int32_t magicNumber, imgSize, rows, cols;
    imgFile.read((char*)&magicNumber, 4);
    imgFile.read((char*)&imgSize, 4);
    imgFile.read((char*)&rows, 4);
    imgFile.read((char*)&cols, 4);
    magicNumber = reverseInt(magicNumber);
    imgSize = reverseInt(imgSize);
    rows = reverseInt(rows);
    cols = reverseInt(cols);
    int imgPixels = rows * cols;

    for (int i = 0; i < imgSize; i++) {
        CImg<unsigned char> img(cols, rows, 1, 1, 0);
        imgFile.read((char*)img.data(), imgPixels);
        imgList.push_back(img);
        vector<unsigned char> imgData(rows * cols, 0);
        memcpy(imgData.data(), img.data(), imgPixels * sizeof(unsigned char));
        imgSet.push_back(imgData);
    }
}

array<unsigned char, 4> digitToBinary(unsigned char digit) {
    return {static_cast<unsigned char>(digit / 8 % 2), static_cast<unsigned char>(digit / 4 % 2),
            static_cast<unsigned char>(digit / 2 % 2), static_cast<unsigned char>(digit % 2)};
};

void readLabelFile(ifstream& labelFile, vector<unsigned char>& labelList, std::vector<std::array<unsigned char, 10>>& labelSet) {
    int32_t magicNumber, imgSize;
    labelFile.read((char*)&magicNumber, 4);
    labelFile.read((char*)&imgSize, 4);
    magicNumber = reverseInt(magicNumber);
    imgSize = reverseInt(imgSize);
    for (int i = 0; i < imgSize; i++) {
        unsigned char label;
        labelFile.read((char*)&label, 1);
        labelList.push_back(label);
        array<unsigned char, 10> newLabel;
        for (int k = 0; k < 10; k++) {
            if (k == label) {
                newLabel[k] = 1;
            } else {
                newLabel[k] = 0;
            }
        }
        labelSet.push_back(newLabel);
    }
}


CImgMNistData::CImgMNistData() {
    ifstream trainImgFile(trainImagePath, ios::binary);
    ifstream testImgFile(testImagePath, ios::binary);
    ifstream trainLabelFile(trainLabelPath, ios::binary);
    ifstream testLabelFile(testLabelPath, ios::binary);

    readImgFile(trainImgFile, trainImg, trainSet);
    readImgFile(testImgFile, testImg, testSet);

    readLabelFile(trainLabelFile, trainLabels, trainBinaryLabels);
    readLabelFile(testLabelFile, testLabels, testBinaryLabels);
}

CImg<unsigned char> CImgMNistData::getTestImage(int index) {
    return testImg[index];
}

CImg<unsigned char> CImgMNistData::getTrainImage(int index) {
    return trainImg[index];
}

int CImgMNistData::getTestLabel(int index) {
    return testLabels[index];
}

int CImgMNistData::getTrainLabel(int index) {
    return trainLabels[index];
}

std::vector<unsigned char> CImgMNistData::getTestImageData(int index) {
    return testSet[index];
}

std::vector<unsigned char> CImgMNistData::getTrainImageData(int index) {
    return trainSet[index];
}

std::vector<std::vector<unsigned char>> CImgMNistData::getTrainSet() {
    return trainSet;
}

std::vector<std::vector<unsigned char>> CImgMNistData::getTestSet() {
    return testSet;
}

std::vector<std::array<unsigned char, 10>> CImgMNistData::getTestBinaryLabels() {
    return testBinaryLabels;
}

std::vector<std::array<unsigned char, 10>> CImgMNistData::getTrainBinaryLabels() {
    return trainBinaryLabels;
}

int CImgMNistData::getTestSize() {
    return testImg.size();
}

int CImgMNistData::getTrainSize() {
    return trainImg.size();
}

