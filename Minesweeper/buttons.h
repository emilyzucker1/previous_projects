//
// Created by Emily Zucker on 4/12/24.
//

#ifndef SFML_BUTTONS_H
#define SFML_BUTTONS_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Button{

public:
    Button(){}

    Button(sf::Sprite sprite, string type){
        button = sprite;
        this->type = type;
    }

    void changeTexture(sf::Texture texture){
        button.setTexture(texture);
    }

    void setPosition(int x, int y){
        button.setPosition(x, y);
    }

    void drawButton(sf::RenderWindow &gameWindow){
        gameWindow.draw(button);
    }

    bool isClicked(int mouseX, int mouseY){
        float buttonPosX = button.getPosition().x;
        float buttonPosY = button.getPosition().y;

        float buttonPosWidth = buttonPosX + button.getLocalBounds().width;
        float buttonPosHeight = buttonPosY + button.getLocalBounds().height;

        if (mouseX < buttonPosWidth && mouseX > buttonPosX
        && mouseY < buttonPosHeight && mouseY > buttonPosY){
            return true;
        }
        else{
            return false;
        }
    }

    bool isSmiley(){
        if (type == "smiley"){
            return true;
        }
        else{
            return false;
        }
    }

    bool isDebug(){
        if (type == "debug"){
            return true;
        }
        else{
            return false;
        }
    }

    bool isPause(){
        if (type == "pause"){
            return true;
        }
        else{
            return false;
        }
    }

    bool isLeaderboard(){
        if (type == "leaderboard"){
            return true;
        }
        else{
            return false;
        }
    }

    void getType(){
        cout << type << endl;
    }


private:
    sf::Sprite button;
    string type;

};




#endif //SFML_BUTTONS_H

