//
// Created by Emily Zucker on 3/12/24.
//

#include "ImageStructs.h"
#include "ImageStructs.cpp"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// function to check name validity.
bool checkName(string fileName){

    // initialize substring target.
    string file_ext = ".tga";
    // initializing position.
    int pos = 0;
    // determine if the name contains target.
    if (fileName.find(file_ext, pos) != string::npos){
        // set new position where the target what found.
        pos = fileName.find(file_ext, pos);
        // if the position isn't at the end of the name its invalid.
        if (pos != fileName.length() - 4){
            return false;
        }
        // if the target appears more than once the name is invalid.
        else if (fileName.find(file_ext, (pos + file_ext.length())) != string::npos) {
            return false;
        }
        // otherwise it's valid.
        return true;
    }
    // if the name doesn't contain the target it is invalid.
    else{
        return false;
    }
}

// function to run methods that require a value argument.
Image valueFunctions(Image &outputImage, string outputFileName, int value, string method, Image &sourceImage){

    // create output ofstream.
    ofstream outputFile(outputFileName, ios::binary);

    // implement method based on name.
    if (method == "addblue"){
        outputImage = sourceImage.addblue(value);
        outputImage.writeToNew(outputFile);
    }
    else if (method == "addgreen"){
        outputImage = sourceImage.addgreen(value);
        outputImage.writeToNew(outputFile);
    }
    else if (method == "addred"){
        outputImage = sourceImage.addred(value);
        outputImage.writeToNew(outputFile);
    }
    else if (method == "scaleblue"){
        outputImage = sourceImage.scaleblue(value);
        outputImage.writeToNew(outputFile);
    }
    else if (method == "scalegreen"){
        outputImage = sourceImage.scalegreen(value);
        outputImage.writeToNew(outputFile);
    }
    else if (method == "scalered"){
        outputImage = sourceImage.scalered(value);
        outputImage.writeToNew(outputFile);
    }

    // return the output image.
    return outputImage;
}

// function to run methods that require an additional file argument excluding combine.
Image additionalImageFunctions(Image &outputImage, string outputFileName, Image &nextImage, string method, Image &sourceImage){

    ofstream outputFile(outputFileName, ios::binary);

    if (method == "multiply"){
        outputImage = sourceImage.multiply(nextImage);
        outputImage.writeToNew(outputFile);
    }
    else if (method == "subtract"){
        outputImage = sourceImage.subtract(nextImage);
       outputImage.writeToNew(outputFile);
    }
    else if (method == "screen"){
        outputImage = sourceImage.screen(nextImage);
        outputImage.writeToNew(outputFile);
    }
    else if (method == "overlay"){
        outputImage = sourceImage.overlay(nextImage);
        outputImage.writeToNew(outputFile);
    }

    return outputImage;

}

// function to run methods that don't require an additional argument.
Image singularFunctions(Image &outputImage, string outputFileName, string method, Image &sourceImage){

    ofstream outputFile(outputFileName, ios::binary);

    if (method == "onlyblue"){
        outputImage = sourceImage.onlyblue();
        outputImage.writeToNew(outputFile);
    }
    else if (method == "onlygreen"){
        outputImage = sourceImage.onlygreen();
        outputImage.writeToNew(outputFile);
    }
    else if (method == "onlyred"){
        outputImage = sourceImage.onlyred();
        outputImage.writeToNew(outputFile);
    }
    else if (method == "flip"){
        outputImage = sourceImage.flip();
        outputImage.writeToNew(outputFile);
    }

    return outputImage;

}

vector<string> removeElement(vector<string> &originalVector, int index){

    vector<string> newVector;

    for (int i = 0; i < index; i++){
        newVector.push_back(originalVector.at(i));
    }
    for (int j = (index + 1); j < (originalVector.size()); j++){
        newVector.push_back(originalVector.at(j));
    }
    return newVector;
}


int main(int argc, char* argv[]) {

    vector<string> arguments;
    for (int i = 0; i < argc; i++){
        arguments.push_back((string)argv[i]);

    }

    // instructions
    if (arguments.size() == 1) {
        cout << "Project 2: Image Processing, Spring 2024\n\nUsage:"
                "\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }
    else if (arguments.size() > 1) {
        if (arguments[1] == "--help") {
            cout << "Project 2: Image Processing, Spring 2024\n\nUsage:"
                    "\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
            return 0;
        }
    }

    try {

        // initialize output file name.
        string outputFileName = arguments[1];
        // create output image object.
        Image outputImage;

        // confirm that file name is valid.
        if (!checkName(outputFileName)) {
            cout << "Invalid file name." << endl;
            return 0;
        }

        // initialize source file.
        string sourceFileName = arguments[2];
        if (!checkName(sourceFileName)) {
            cout << "Invalid file name." << endl;
            return 0;
        }

        // create ifstream file.
        ifstream sourceFile(sourceFileName, ios::binary);

        // confirm source file exists and is open.
        if (!sourceFile) {
            cout << "File does not exist.";
            return 0;
        }

        // create source image object.
        Image sourceImage(sourceFile);

        // check that there is a method argument.
        if (arguments.size() == 3) {
            cout << "Invalid method name.";
            return 0;
        }

        bool proceed = true;
        while (proceed) {

            // initialize method name.
            string method = arguments[3];

            // if method does not match one of the specified, it is invalid.
            if (method != "multiply" && method != "subtract" && method != "screen" &&
                method != "overlay" && method != "combine" && method != "flip" &&
                method.find("add") == string::npos && method.find("scale") == string::npos &&
                method.find("only") == string::npos) {
                cout << "Invalid method name." << endl;
                return 0;
            }

            // identify if method requires other args.
            if (method != "flip" && method.find("only") == string::npos) {
                // if there is no argument for the next file...
                if (arguments.size() == 4) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                    // if there is an argument for the next file or a number...
                else {
                    // check if method requires a number argument.
                    if (method.find("add") != string::npos || method.find("scale") != string::npos) {

                        try {
                            // confirm that the argument can be made into an int value.
                            int value = stoi(arguments[4]);
                            // then run the method and return it as the output tracking image object.
                            outputImage = valueFunctions(outputImage, outputFileName, value, method, sourceImage);
                            arguments = removeElement(arguments, 3);
                            arguments = removeElement(arguments, 3);
                        }
                            // if the argument can not be made into an int, then the argument is invalid.
                        catch (exception &e) {
                            cerr << "Invalid argument, expected number." << endl;
                            return 0;
                        }
                    }
                    // if the method requires a file argument...
                    else {
                        // initialize the name of the next file.
                        string nextFileName = arguments[4];

                        // confirm the file exists.
                        if (!checkName(nextFileName)) {
                            cout << "Invalid argument, invalid file name." << endl;
                            return 0;
                        }

                        // open file and confirm it's open.
                        ifstream nextFile(nextFileName, ios::binary);
                        if (!nextFile) {
                            cout << "Invalid argument, file does not exist." << endl;
                            return 0;
                        }

                        // create next image object.
                        Image nextImage(nextFile);
                        // implement method.

                        if (method == "combine"){
                            string nextNextFileName = arguments[5];
                            if (!checkName(nextNextFileName)){
                                cout << "Invalid argument, invalid file name." << endl;
                                return 0;
                            }
                            ifstream nextNextFile(nextNextFileName, ios::binary);
                            if (!nextNextFile){
                                cout << "Invalid argument, file does not exist." << endl;
                                return 0;
                            }
                            Image nextNextImage(nextNextFile);
                            outputImage = sourceImage.combine(nextImage, nextNextImage);
                            ofstream outputFile(outputFileName, ios::binary);
                            outputImage.writeToNew(outputFile);
                            arguments = removeElement(arguments, 3);
                            arguments = removeElement(arguments, 3);
                            arguments = removeElement(arguments, 3);

                        }
                        else {
                            outputImage = additionalImageFunctions(outputImage, outputFileName, nextImage, method,
                                                                   sourceImage);
                            arguments = removeElement(arguments, 3);
                            arguments = removeElement(arguments, 3);
                        }
                    }
                }
            }
            else {
                // if the method requires no additional arguments, run that method and return output image.
                outputImage = singularFunctions(outputImage, outputFileName, method, sourceImage);
                arguments = removeElement(arguments, 3);
            }

            sourceImage = outputImage;

            if (arguments.size() == 3){
                proceed = false;
            }
        }
    }
    catch(exception &e){
        cerr << "something went wrong." << endl;
    }



    return 0;
}