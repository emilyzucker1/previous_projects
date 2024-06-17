//
// Created by Emily Zucker on 3/12/24.
//

#ifndef PRACTICE_IMAGESTRUCTS_H
#define PRACTICE_IMAGESTRUCTS_H
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Image{

    struct Pixel{
        unsigned char blue;
        unsigned char green;
        unsigned char red;

        Pixel(){
            blue = 0;
            green = 0;
            red = 0;
        }

        Pixel(unsigned char b, unsigned char g, unsigned char r){
            blue = b;
            green = g;
            red = r;
        }

        bool operator==(Pixel &otherPixel){
            if (blue != otherPixel.blue){
                return false;
            }
            else if (green != otherPixel.green){
                return false;
            }
            else if (red != otherPixel.red){
                return false;
            }
            else{
                return true;
            }
        }

    };

    unsigned char idLength;
    unsigned char colorMapType;
    unsigned char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    unsigned char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    unsigned char bitsPerPixel;
    unsigned char imageDescriptor;
    vector<Pixel> pixelData;
    int numPixels;

    Image();

    Image(ifstream &file);

    void writeToNew(ofstream &newFile);

    void setHeaderEqual(Image &otherImage);

    Image multiply(Image &otherImage);

    Image subtract(Image &otherImage);

    Image screen(Image &otherImage);

    Image overlay(Image &otherImage);

    Image addblue(int value);
    Image addgreen(int value);
    Image addred(int value);

    Image scaleblue(int value);
    Image scalegreen(int value);
    Image scalered(int value);

    Image onlyblue();
    Image onlygreen();
    Image onlyred();

    Image combine(Image &image1, Image &image2);

    Image flip();

};



#endif //PRACTICE_IMAGESTRUCTS_H
