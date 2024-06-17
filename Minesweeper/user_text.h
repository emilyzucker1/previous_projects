//
// Created by Emily Zucker on 4/15/24.
//

#ifndef SFML_USER_TEXT_H
#define SFML_USER_TEXT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace std;

#define DELETE_KEY 8
#define ENTER_KEY 13

class Usertext{

public:
    Usertext(){
        usertext.setString("|");
    }

    void setFont(sf::Font &font){
        usertext.setFont(font);
        usertext.setCharacterSize(18);
        usertext.setFillColor(sf::Color::Yellow);
    }

    void setPos(float x, float y){
        sf::FloatRect textRect = usertext.getLocalBounds();
        usertext.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        usertext.setPosition(sf::Vector2f(x, y));
    }

    void drawText(sf::RenderWindow &window){
        window.draw(usertext);
    }

    void Type(sf::Event event){
        int keyTyped = event.text.unicode;
        if ((keyTyped >= 65 && keyTyped <= 90) || (keyTyped >= 97 && keyTyped <= 122)){
            if (input.str().length() < limit){
                userInput(keyTyped);
            }
        }
        else if (keyTyped == DELETE_KEY){
            userInput(keyTyped);
        }
    }

    string getText(){
        return input.str();
    }



private:
    sf::Text usertext;
    ostringstream input;
    int limit = 10;

    void userInput(int keyTyped){
        if (keyTyped != DELETE_KEY && keyTyped != ENTER_KEY){
            if (input.str().length() == 0){
                input << char(toupper(static_cast<char>(keyTyped)));
            }
            else{
                input << char(tolower(static_cast<char>(keyTyped)));
            }
        }
        else if (keyTyped == DELETE_KEY){
            if (input.str().length() > 0){
                deleteChar();
            }
        }
        usertext.setString(input.str() + "|");
    }

    void deleteChar(){
        string oldtext = input.str();
        string newtext = "";
        for (int i = 0; i < oldtext.length() - 1; i++){
            newtext += oldtext[i];
        }
        input.str("");
        input << newtext;

        usertext.setString(input.str());
    }

};

#endif //SFML_USER_TEXT_H
