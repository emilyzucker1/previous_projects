//
// Created by Emily Zucker on 3/12/24.
//
#include "ImageStructs.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

Image::Image() {
        idLength = 0;
        colorMapType = 0;
        dataTypeCode = 0;
        colorMapOrigin = 0;
        colorMapLength = 0;
        colorMapDepth = 0;
        xOrigin = 0;
        yOrigin = 0;
        width = 0;
        height = 0;
        bitsPerPixel = 0;
        imageDescriptor = 0;
        numPixels = 0;
}

Image::Image(ifstream &file) {
    file.read((char*)&idLength, sizeof(idLength));
    file.read((char*)&colorMapType, sizeof(colorMapType));
    file.read((char*)&dataTypeCode, sizeof(dataTypeCode));
    file.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
    file.read((char*)&colorMapLength, sizeof(colorMapLength));
    file.read((char*)&colorMapDepth, sizeof(colorMapDepth));
    file.read((char*) &xOrigin, sizeof(xOrigin));
    file.read((char*) &yOrigin, sizeof(yOrigin));
    file.read((char*) &width, sizeof(width));
    file.read((char*) &height, sizeof(height));
    file.read((char*)&bitsPerPixel, sizeof(bitsPerPixel));
    file.read((char*)&imageDescriptor, sizeof(imageDescriptor));
    numPixels = width * height;
    unsigned char b;
    unsigned char g;
    unsigned char r;
    for (int i = 0; i < (width * height); i++) {
        file.read((char*)&b, sizeof(b));
        file.read((char*)&g, sizeof(g));
        file.read((char*)&r, sizeof(r));
        Pixel pixel(b, g, r);
        pixelData.push_back(pixel);
    }
    file.close();
}


void Image::writeToNew(ofstream &newFile) {
    newFile.write((char*)&idLength, sizeof(idLength));
    newFile.write((char*)&colorMapType, sizeof(colorMapType));
    newFile.write((char*)&dataTypeCode, sizeof(dataTypeCode));
    newFile.write((char*)&colorMapOrigin, sizeof(colorMapOrigin));
    newFile.write((char*) &colorMapLength, sizeof(colorMapLength));
    newFile.write((char*)&colorMapDepth, sizeof(colorMapDepth));
    newFile.write((char*) &xOrigin, sizeof(xOrigin));
    newFile.write((char*) &yOrigin, sizeof(yOrigin));
    newFile.write((char*) &width, sizeof(width));
    newFile.write((char*) &height, sizeof(height));
    newFile.write((char*)&bitsPerPixel, sizeof(bitsPerPixel));
    newFile.write((char*)&imageDescriptor, sizeof(imageDescriptor));
    for (int i = 0; i < numPixels; i++){
        unsigned char blue = pixelData.at(i).blue;
        newFile.write((char*)&blue, sizeof(blue));
        unsigned char green = pixelData.at(i).green;
        newFile.write((char*)&green, sizeof(green));
        unsigned char red = pixelData.at(i).red;
        newFile.write((char*)&red, sizeof(red));
    }
}


void Image::setHeaderEqual(Image &otherImage){
    otherImage.idLength = idLength;
    otherImage.colorMapType = colorMapType;
    otherImage.dataTypeCode = dataTypeCode;
    otherImage.colorMapOrigin = colorMapOrigin;
    otherImage.colorMapLength = colorMapLength;
    otherImage.colorMapDepth = colorMapDepth;
    otherImage.xOrigin = xOrigin;
    otherImage.yOrigin = yOrigin;
    otherImage.width = width;
    otherImage.height = height;
    otherImage.bitsPerPixel = bitsPerPixel;
    otherImage.imageDescriptor = imageDescriptor;
    otherImage.numPixels = numPixels;
}


Image Image::multiply(Image &otherImage) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newBlue;
    unsigned char newGreen;
    unsigned char newRed;
    float nP1;
    float nP2;
    for (int i = 0; i < numPixels; i++){
        nP1 = (float)(pixelData.at(i).blue) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).blue) / 255;
        newBlue = (unsigned char)(((nP1 * nP2) * 255) + 0.5f);
        nP1 = (float)(pixelData.at(i).green) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).green) / 255;
        newGreen = (unsigned char)(((nP1 * nP2) * 255) + 0.5f);
        nP1 = (float)(pixelData.at(i).red) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).red) / 255;
        newRed = (unsigned char)(((nP1 * nP2) * 255) + 0.5f);
        Pixel pixel(newBlue, newGreen, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::subtract(Image &otherImage) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newBlue;
    unsigned char newGreen;
    unsigned char newRed;
    int tempBlue;
    int tempGreen;
    int tempRed;
    for (int i = 0; i < numPixels; i++){
        tempBlue = ((int)(pixelData.at(i).blue) - (int)(otherImage.pixelData.at(i).blue));
        if (tempBlue < 0){
            newBlue = (unsigned char)(0);
        }
        else if (tempBlue > 255){
            newBlue = (unsigned char)(255);
        }
        else{
            newBlue = (unsigned char)(tempBlue);
        }
        tempGreen = ((int)(pixelData.at(i).green) - (int)(otherImage.pixelData.at(i).green));
        if (tempGreen < 0){
            newGreen = (unsigned char)(0);
        }
        else if (tempGreen > 255){
            newGreen = (unsigned char)(255);
        }
        else{
            newGreen = (unsigned char)(tempGreen);
        }
        tempRed = ((int)(pixelData.at(i).red) - (int)(otherImage.pixelData.at(i).red));
        if (tempRed < 0){
            newRed = (unsigned char)(0);
        }
        else if (tempRed > 255){
            newRed = (unsigned char)(255);
        }
        else{
            newRed = (unsigned char)(tempRed);
        }
        Pixel pixel(newBlue, newGreen, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::screen(Image &otherImage) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newBlue;
    unsigned char newGreen;
    unsigned char newRed;
    float nP1;
    float nP2;
    for (int i = 0; i < numPixels; i++){
        nP1 = (float)(pixelData.at(i).blue) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).blue) / 255;
        newBlue = (unsigned char)(((1 - ((1 - nP1) * (1 - nP2))) * 255) + 0.5f);
        nP1 = (float)(pixelData.at(i).green) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).green) / 255;
        newGreen = (unsigned char)(((1 - ((1 - nP1) * (1 - nP2))) * 255) + 0.5f);
        nP1 = (float)(pixelData.at(i).red) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).red) / 255;
        newRed = (unsigned char)(((1 - ((1 - nP1) * (1 - nP2))) * 255) + 0.5f);
        Pixel pixel(newBlue, newGreen, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::overlay(Image &otherImage) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newBlue;
    unsigned char newGreen;
    unsigned char newRed;
    float nP1;
    float nP2;
    for (int i = 0; i < numPixels; i++) {
        nP1 = (float)(pixelData.at(i).blue) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).blue) / 255;
        if (nP2 <= 0.5){
            newBlue = (unsigned char)(((2 * nP1 * nP2) * 255) + 0.5f);
        }
        else{
            newBlue = (unsigned char)(((1 - (2 * (1 - nP1) * (1 - nP2))) * 255) + 0.5f);
        }
        nP1 = (float)(pixelData.at(i).green) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).green) / 255;
        if (nP2 <= 0.5){
            newGreen = (unsigned char)(((2 * nP1 * nP2) * 255) + 0.5f);
        }
        else{
            newGreen = (unsigned char)(((1 - (2 * (1 - nP1) * (1 - nP2))) * 255) + 0.5f);
        }
        nP1 = (float)(pixelData.at(i).red) / 255;
        nP2 = (float)(otherImage.pixelData.at(i).red) / 255;
        if (nP2 <= 0.5){
            newRed = (unsigned char)(((2 * nP1 * nP2) * 255) + 0.5f);
        }
        else{
            newRed = (unsigned char)(((1 - (2 * (1 - nP1) * (1 - nP2))) * 255) + 0.5f);
        }
        Pixel pixel(newBlue, newGreen, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::addblue(int value) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    int tempBlue;
    unsigned char newBlue;
    for (int i = 0; i < numPixels; i++){
        tempBlue = ((int)(pixelData.at(i).blue) + value);
        if (tempBlue > 255){
            newBlue = (unsigned char)(255);
        }
        else if (tempBlue < 0){
            newBlue = (unsigned char)(0);
        }
        else{
            newBlue = (unsigned char)(tempBlue);
        }
        Pixel pixel(newBlue, pixelData.at(i).green, pixelData.at(i).red);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::addgreen(int value) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    int tempGreen;
    unsigned char newGreen;
    for (int i = 0; i < numPixels; i++){
        tempGreen = ((int)(pixelData.at(i).green) + value);
        if (tempGreen > 255){
            newGreen = (unsigned char)(255);
        }
        else if (tempGreen < 0){
            newGreen = (unsigned char)(0);
        }
        else{
            newGreen = (unsigned char)(tempGreen);
        }
        Pixel pixel(pixelData.at(i).blue, newGreen, pixelData.at(i).red);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::addred(int value) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    int tempRed;
    unsigned char newRed;
    for (int i = 0; i < numPixels; i++){
        tempRed = ((int)(pixelData.at(i).red) + value);
        if (tempRed > 255){
            newRed = (unsigned char)(255);
        }
        else if (tempRed < 0){
            newRed = (unsigned char)(0);
        }
        else{
            newRed = (unsigned char)(tempRed);
        }
        Pixel pixel(pixelData.at(i).blue, pixelData.at(i).green, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::scaleblue(int value) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    int tempBlue;
    unsigned char newBlue;
    for (int i = 0; i < numPixels; i++){
        tempBlue = ((int)(pixelData.at(i).blue)) * value;
        if (tempBlue > 255){
            newBlue = (unsigned char)(255);
        }
        else{
            newBlue = (unsigned char)(tempBlue);
        }
        Pixel pixel(newBlue, pixelData.at(i).green, pixelData.at(i).red);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::scalegreen(int value) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    int tempGreen;
    unsigned char newGreen;
    for (int i = 0; i < numPixels; i++){
        tempGreen = ((int)(pixelData.at(i).green)) * value;
        if (tempGreen > 255){
            newGreen = (unsigned char)(255);
        }
        else{
            newGreen = (unsigned char)(tempGreen);
        }
        Pixel pixel(pixelData.at(i).blue, newGreen, pixelData.at(i).red);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::scalered(int value) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    int tempRed;
    unsigned char newRed;
    for (int i = 0; i < numPixels; i++){
        tempRed = ((int)(pixelData.at(i).red)) * value;
        if (tempRed > 255){
            newRed = (unsigned char)(255);
        }
        else{
            newRed = (unsigned char)(tempRed);
        }
        Pixel pixel(pixelData.at(i).blue, pixelData.at(i).green, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::onlyblue() {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newBlue;
    for (int i = 0; i < numPixels; i++){
        newBlue = pixelData.at(i).blue;
        Pixel pixel(newBlue, newBlue, newBlue);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::onlygreen() {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newGreen;
    for (int i = 0; i < numPixels; i++){
        newGreen = pixelData.at(i).green;
        Pixel pixel(newGreen, newGreen, newGreen);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::onlyred() {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newRed;
    for (int i = 0; i < numPixels; i++){
        newRed = pixelData.at(i).red;
        Pixel pixel(newRed, newRed, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::combine(Image &image1, Image &image2) {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newBlue;
    unsigned char newGreen;
    unsigned char newRed;
    for (int i = 0; i < numPixels; i++){
        newRed = pixelData.at(i).red;
        newGreen = image1.pixelData.at(i).green;
        newBlue = image2.pixelData.at(i).blue;
        Pixel pixel(newBlue, newGreen, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}


Image Image::flip() {
    Image newImage;
    setHeaderEqual(newImage);
    vector<Pixel> newPixelData;
    unsigned char newBlue;
    unsigned char newGreen;
    unsigned char newRed;
    for (int i = (numPixels - 1); i >= 0; i--){
        newBlue = pixelData.at(i).blue;
        newGreen = pixelData.at(i).green;
        newRed = pixelData.at(i).red;
        Pixel pixel(newBlue, newGreen, newRed);
        newPixelData.push_back(pixel);
    }
    newImage.pixelData = newPixelData;
    return newImage;
}