//
// Created by Emily Zucker on 4/19/24.
//

#ifndef SFML_COUNTERS_H
#define SFML_COUNTERS_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace std;

class FlagCounter{

public:
    FlagCounter(){}

    FlagCounter(sf::Sprite digit_one, sf::Sprite digit_two, sf::Sprite digit_three, sf::Sprite negative, sf::Texture texture, int num_mines){
        this->digit_one = digit_one;
        this->digit_two = digit_two;
        this->digit_three = digit_three;
        this->negative = negative;
        flag_counter_texture = texture;
        num_flags_remaining = num_mines;
        neg_flags = 0;
        dig_three = num_flags_remaining % 10;
        dig_two = (num_flags_remaining / 10) % 10;
        dig_one = (num_flags_remaining / 100) % 10;
    }

    void flagPlaced(){
        num_flags_remaining--;
        if (num_flags_remaining >= 0) {
            dig_three = num_flags_remaining % 10;
            dig_two = (num_flags_remaining / 10) % 10;
            dig_one = (num_flags_remaining / 100) % 10;
        }
        else{
            neg_flags++;
            dig_three = neg_flags % 10;
            dig_two = (neg_flags / 10) % 10;
            dig_one = (neg_flags / 100) % 10;
        }
    }

    void flagRemoved(){
        num_flags_remaining++;
        if (num_flags_remaining >= 0) {
            dig_three = num_flags_remaining % 10;
            dig_two = (num_flags_remaining / 10) % 10;
            dig_one = (num_flags_remaining / 100) % 10;
        }
        else{
            neg_flags--;
            dig_three = neg_flags % 10;
            dig_two = (neg_flags / 10) % 10;
            dig_one = (neg_flags / 100) % 10;
        }
    }

    void setPosition(int posX, int posY){
        digit_one.setPosition(posX, posY);
        digit_two.setPosition((posX + 21), posY);
        digit_three.setPosition((posX + 42), posY);
        negative.setPosition((posX - 21), posY);
    }

    void drawFlagCounter(sf::RenderWindow &gameWindow){
        digit_one.setTextureRect(sf::IntRect((21 * dig_one), 0, 21, 32));
        gameWindow.draw(digit_one);
        digit_two.setTextureRect(sf::IntRect((21 * dig_two), 0, 21, 32));
        gameWindow.draw(digit_two);
        digit_three.setTextureRect(sf::IntRect((21 * dig_three), 0, 21, 32));
        gameWindow.draw(digit_three);
        if (num_flags_remaining < 0){
            negative.setTextureRect(sf::IntRect((21 * 10), 0, 21, 32));
            gameWindow.draw(negative);
        }
    }




private:
    int num_flags_remaining, neg_flags, dig_one, dig_two, dig_three;
    sf::Sprite digit_one;
    sf::Sprite digit_two;
    sf::Sprite digit_three;
    sf::Sprite negative;
    sf::Texture flag_counter_texture;

};


class TimeCounter{

public:
    TimeCounter(){}

    TimeCounter(sf::Clock clock, sf::Texture texture, sf::Sprite first_digit_minutes, sf::Sprite second_digit_minutes,
                sf::Sprite first_digit_seconds, sf::Sprite second_digit_seconds){
        this->clock = clock;
        this->texture = texture;
        total_minutes = 0;
        minutes_one = 0;
        minutes_two = 0;
        total_seconds = 0;
        seconds_one = 0;
        seconds_two = 0;
        stopped_total_minutes = 0;
        stopped_minutes_one = 0;
        stopped_minutes_two = 0;
        stopped_total_seconds = 0;
        stopped_seconds_one = 0;
        stopped_seconds_two = 0;
        this->first_digit_minutes = first_digit_minutes;
        this->second_digit_minutes = second_digit_minutes;
        this->first_digit_seconds = first_digit_seconds;
        this->second_digit_seconds = second_digit_seconds;
        stop = false;
    }

    void setPosition(int posX, int posY){
        first_digit_minutes.setPosition(posX, posY);
        second_digit_minutes.setPosition((posX + 21), posY);
        first_digit_seconds.setPosition((posX + 43), posY);
        second_digit_seconds.setPosition((posX + 64), posY);
    }

    void drawTimeCounter(sf::RenderWindow &gameWindow){
        if (!stop) {
            total_seconds = ((int)(clock.getElapsedTime().asSeconds())) - stopped_total_seconds;
            if (total_seconds == 60) {
                total_minutes++;
                total_seconds = 0;
                clock.restart();
            }
            seconds_one = ((int)((clock.getElapsedTime().asSeconds() - stopped_seconds_two) / 10) % 10);
            seconds_two = ((int)((clock.getElapsedTime().asSeconds())  - stopped_seconds_two) % 10);
            minutes_one = ((total_minutes / 10) % 10) - stopped_minutes_one;
            minutes_two = (total_minutes % 10) - stopped_minutes_two;
        }
        else{
            stopped_total_seconds = (int)(clock.getElapsedTime().asSeconds()) - total_seconds;
            if (stopped_total_seconds == 60) {
                stopped_total_minutes++;
                stopped_total_seconds = 0;
                clock.restart();
            }
            stopped_seconds_one = ((int)((clock.getElapsedTime().asSeconds() - seconds_two) / 10) % 10);
            stopped_seconds_two = ((int)(clock.getElapsedTime().asSeconds() - seconds_two) % 10);
            stopped_minutes_one = ((stopped_total_minutes / 10) % 10) - minutes_one;
            stopped_minutes_two = (stopped_total_minutes % 10) - minutes_two;
        }
        first_digit_minutes.setTextureRect(sf::IntRect((21 * minutes_one), 0, 21, 32));
        gameWindow.draw(first_digit_minutes);
        second_digit_minutes.setTextureRect(sf::IntRect((21 * minutes_two), 0, 21, 32));
        gameWindow.draw(second_digit_minutes);
        first_digit_seconds.setTextureRect(sf::IntRect((21 * seconds_one), 0, 21, 32));
        gameWindow.draw(first_digit_seconds);
        second_digit_seconds.setTextureRect(sf::IntRect((21 * seconds_two), 0, 21, 32));
        gameWindow.draw(second_digit_seconds);
    }

    void resetCounter(){
        total_minutes = 0;
        minutes_one = 0;
        minutes_two = 0;
        seconds_one = 0;
        seconds_two = 0;
        stopped_total_minutes = 0;
        stopped_minutes_one = 0;
        stopped_minutes_two = 0;
        stopped_seconds_one = 0;
        stopped_seconds_two = 0;
        clock.restart();
    }

    void stopTime(){
        stop = true;
    }

    void startTime(){
        stop = false;
    }

    string getTime(){
        string time;
        time += to_string(minutes_one);
        time += to_string(minutes_two);
        time += ":";
        time += to_string(seconds_one);
        time += to_string(seconds_two);
        return time;
    }

private:
    int seconds_one, seconds_two, minutes_one, minutes_two, total_seconds, total_minutes;
    int stopped_seconds_one, stopped_seconds_two, stopped_minutes_one, stopped_minutes_two, stopped_total_seconds, stopped_total_minutes;
    sf::Clock clock;
    sf::Texture texture;
    sf::Sprite first_digit_minutes;
    sf::Sprite second_digit_minutes;
    sf::Sprite first_digit_seconds;
    sf::Sprite second_digit_seconds;
    bool stop;

};


#endif //SFML_COUNTERS_H
