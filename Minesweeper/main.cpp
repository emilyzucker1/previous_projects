//
// Created by Emily Zucker on 4/12/24.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "user_text.h"
#include "buttons.h"
#include "mines.h"
#include "counters.h"
using namespace std;

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void displayWelcome(int welcomeWidth, int welcomeHeight, sf::RenderWindow &welcomeWindow, sf::Font &welcomeFont){

    sf::Text welcomeText("WELCOME TO MINESWEEPER!", welcomeFont, 24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    setText(welcomeText, (welcomeWidth / 2), ((welcomeHeight / 2) - 150));

    sf::Text nameText("Enter your name:", welcomeFont, 20);
    nameText.setStyle(sf::Text::Bold);
    nameText.setFillColor(sf::Color::White);
    setText(nameText, (welcomeWidth / 2), ((welcomeHeight / 2) - 75));

    welcomeWindow.draw(welcomeText);
    welcomeWindow.draw(nameText);

}

string getStats(){
    vector<string> leaderboard_stats;
    string line, name, time;
    ifstream leaderboard_file("files/leaderboard.txt");
    while (getline(leaderboard_file, line)){
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, time, ',');
        leaderboard_stats.push_back(name);
        leaderboard_stats.push_back(time);
    }

    int place = 0;
    string stats;

    stats += "1.\t";
    stats += leaderboard_stats.at(place);
    stats += "\t";
    stats += leaderboard_stats.at(place + 1);
    stats += "\n\n";

    stats += "2.\t";
    stats += leaderboard_stats.at(place + 2);
    stats += "\t";
    stats += leaderboard_stats.at(place + 3);
    stats += "\n\n";

    stats += "3.\t";
    stats += leaderboard_stats.at(place + 4);
    stats += "\t";
    stats += leaderboard_stats.at(place + 5);
    stats += "\n\n";

    stats += "4.\t";
    stats += leaderboard_stats.at(place + 6);
    stats += "\t";
    stats += leaderboard_stats.at(place + 7);
    stats += "\n\n";

    stats += "5.\t";
    stats += leaderboard_stats.at(place + 8);
    stats += "\t";
    stats += leaderboard_stats.at(place + 9);
    stats += "\n\n";

    return stats;
}

void displayLeaderboard(int leaderboardWidth, int leaderboardHeight, sf::RenderWindow &leaderboardWindow, sf::Font font, string stats){

    sf::Text leaderboardText("LEADERBOARD", font, 20);
    leaderboardText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboardText.setFillColor(sf::Color::White);
    setText(leaderboardText, (leaderboardWidth / 2), ((leaderboardHeight / 2) - 120));

    sf::Text leaderboardStats(stats, font, 18);
    leaderboardStats.setStyle(sf::Text::Bold);
    leaderboardStats.setFillColor(sf::Color::White);
    setText(leaderboardStats, (leaderboardWidth / 2), ((leaderboardHeight / 2) + 20));

    leaderboardWindow.draw(leaderboardText);
    leaderboardWindow.draw(leaderboardStats);

}


int main(){

    string cols, rows, mines;
    ifstream config("files/config.cfg");
    getline(config, cols);
    getline(config, rows);
    getline(config, mines);

    float num_columns = stof(cols);
    float num_rows = stof(rows);
    float num_mines = stof(mines);

    float windowWidth = (num_columns * 32);
    float windowHeight = (num_rows * 32) + 100;

    float leaderboardWidth = (num_columns * 16);
    float leaderboardHeight = ((num_rows * 16) + 50);

    sf::RenderWindow welcomeWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    welcomeWindow.clear(sf::Color::Blue);
    sf::Font welcomeFont;
    welcomeFont.loadFromFile("files/font.ttf");

    string user_name;
    Usertext textbox;
    textbox.setFont(welcomeFont);
    textbox.setPos((windowWidth / 2), ((windowHeight / 2) - 45));

    while (welcomeWindow.isOpen()) {

        sf::Event event;

        while (welcomeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                welcomeWindow.close();
                return 0;
            }
            if (event.type == sf::Event::TextEntered){
                textbox.Type(event);
                textbox.setPos((windowWidth / 2), ((windowHeight / 2) - 45));
                user_name = textbox.getText();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                if (user_name.length() >= 1) {
                    welcomeWindow.close();
                }
            }
        }
        welcomeWindow.clear(sf::Color::Blue);
        displayWelcome(windowWidth, windowHeight, welcomeWindow, welcomeFont);
        textbox.drawText(welcomeWindow);
        welcomeWindow.display();
    }

    sf::RenderWindow gameWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    gameWindow.clear(sf::Color::White);

    sf::Texture smileyTexture;
    smileyTexture.loadFromFile("files/images/face_happy.png");
    sf::Sprite smileySprite(smileyTexture);
    Button smileyButton(smileySprite, "smiley");
    smileyButton.setPosition((((num_columns / 2) * 32) - 32), (32 * (num_rows + 0.5)));

    sf::Texture sadfaceTexture;
    sadfaceTexture.loadFromFile("files/images/face_lose.png");
    sf::Sprite sadfaceSprite(sadfaceTexture);
    Button sadfaceButton(sadfaceSprite, "smiley");
    sadfaceButton.setPosition((((num_columns / 2) * 32) - 32), (32 * (num_rows + 0.5)));

    sf::Texture winfaceTexture;
    winfaceTexture.loadFromFile("files/images/face_win.png");
    sf::Sprite winfaceSprite(winfaceTexture);
    Button winfaceButton(winfaceSprite, "smiley");
    winfaceButton.setPosition((((num_columns / 2) * 32) - 32), (32 * (num_rows + 0.5)));

    sf::Texture debugTexture;
    debugTexture.loadFromFile("files/images/debug.png");
    sf::Sprite debugSprite(debugTexture);
    Button debugButton(debugSprite, "smiley");
    debugButton.setPosition(((num_columns * 32) - 304), (32 * (num_rows + 0.5)));

    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("files/images/pause.png");
    sf::Sprite pauseSprite(pauseTexture);
    Button pauseButton(pauseSprite, "pause");
    pauseButton.setPosition(((num_columns * 32) - 240), (32 * (num_rows + 0.5)));

    sf::Texture playTexture;
    playTexture.loadFromFile("files/images/play.png");
    sf::Sprite playSprite(playTexture);
    Button playButton(playSprite, "pause");
    playButton.setPosition(((num_columns * 32) - 240), (32 * (num_rows + 0.5)));


    sf::Texture leaderboardTexture;
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    sf::Sprite leaderboardSprite(leaderboardTexture);
    Button leaderboardButton(leaderboardSprite, "smiley");
    leaderboardButton.setPosition(((num_columns * 32) - 176), (32 * (num_rows + 0.5)));

    sf::Texture counter;
    counter.loadFromFile("files/images/digits.png");
    sf::Sprite digit_one(counter);
    sf::Sprite digit_two(counter);
    sf::Sprite digit_three(counter);
    sf::Sprite negative(counter);
    FlagCounter flagCounter(digit_one, digit_two, digit_three, negative, counter, num_mines);
    flagCounter.setPosition(33, ((32 * (num_rows + 0.5)) + 16));

    sf::Clock clock;
    sf::Sprite first_digit_minutes(counter);
    sf::Sprite second_digit_minutes(counter);
    sf::Sprite first_digit_seconds(counter);
    sf::Sprite second_digit_seconds(counter);
    TimeCounter timeCounter(clock, counter, first_digit_minutes, second_digit_minutes, first_digit_seconds, second_digit_seconds);
    timeCounter.setPosition(((num_columns * 32) - 97), ((32 * (num_rows + 0.5)) + 16));


    sf::Texture hidden_tile;
    hidden_tile.loadFromFile("files/images/tile_hidden.png");
    sf::Texture revealed_tile;
    revealed_tile.loadFromFile("files/images/tile_revealed.png");
    sf::Texture flag_texture;
    flag_texture.loadFromFile("files/images/flag.png");
    sf::Texture mine_texture;
    mine_texture.loadFromFile("files/images/mine.png");
    sf::Texture number_1_texture;
    number_1_texture.loadFromFile("files/images/number_1.png");
    sf::Texture number_2_texture;
    number_2_texture.loadFromFile("files/images/number_2.png");
    sf::Texture number_3_texture;
    number_3_texture.loadFromFile("files/images/number_3.png");
    sf::Texture number_4_texture;
    number_4_texture.loadFromFile("files/images/number_4.png");
    sf::Texture number_5_texture;
    number_5_texture.loadFromFile("files/images/number_5.png");
    sf::Texture number_6_texture;
    number_6_texture.loadFromFile("files/images/number_6.png");
    sf::Texture number_7_texture;
    number_7_texture.loadFromFile("files/images/number_7.png");
    sf::Texture number_8_texture;
    number_8_texture.loadFromFile("files/images/number_8.png");
    sf::Sprite number_sprite;

    GameBoard gameBoard(num_rows, num_columns, hidden_tile, revealed_tile, flag_texture, mine_texture,
                        number_sprite, number_1_texture, number_2_texture, number_3_texture, number_4_texture,
                        number_5_texture, number_6_texture, number_7_texture, number_8_texture);
    gameBoard.assignMines(num_mines);
    gameBoard.findZoneValues();
    bool debugging = false;
    bool gameOver = false;
    bool paused = false;
    bool writeToLeader = true;

    while (gameWindow.isOpen()){

        sf::Event event;
        if (!gameOver) {
            while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gameWindow.close();
                    return 0;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Mouse mouse;
                    int mousex = mouse.getPosition(gameWindow).x;
                    int mousey = mouse.getPosition(gameWindow).y;
                    if ((mousex >= 0 && mousex <= (windowWidth)) &&
                        (mousey >= 0 && mousey <= (num_rows * 32))) {
                        gameBoard.revealTile(mousex, mousey);
                        if (gameBoard.getMineStatus(mousex, mousey)) {
                            gameOver = true;
                        }
                    }
                    if (smileyButton.isClicked(mousex, mousey)) {
                        GameBoard newBoard(num_rows, num_columns, hidden_tile, revealed_tile, flag_texture,
                                           mine_texture,
                                           number_sprite, number_1_texture, number_2_texture, number_3_texture,
                                           number_4_texture,
                                           number_5_texture, number_6_texture, number_7_texture, number_8_texture);
                        newBoard.assignMines(num_mines);
                        newBoard.findZoneValues();
                        gameBoard = newBoard;
                        FlagCounter newFlagCounter(digit_one, digit_two, digit_three, negative, counter, num_mines);
                        newFlagCounter.setPosition(33, ((32 * (num_rows + 0.5)) + 16));
                        flagCounter = newFlagCounter;
                        timeCounter.resetCounter();
                    }
                    if (leaderboardButton.isClicked(mousex, mousey)) {
                        gameBoard.pause();
                        gameBoard.drawPause(gameWindow);
                        timeCounter.stopTime();
                        sf::RenderWindow leaderboardWindow(sf::VideoMode(leaderboardWidth, leaderboardHeight),
                                                           "Minesweeper");
                        leaderboardWindow.clear(sf::Color::Blue);
                        while (leaderboardWindow.isOpen()) {
                            sf::Event event1;
                            while (leaderboardWindow.pollEvent(event1)) {
                                if (event1.type == sf::Event::Closed) {
                                    leaderboardWindow.close();
                                    timeCounter.startTime();
                                }
                            }
                            leaderboardWindow.clear(sf::Color::Blue);
                            string leader_stats = getStats();
                            displayLeaderboard(leaderboardWidth, leaderboardHeight, leaderboardWindow, welcomeFont, leader_stats);
                            leaderboardWindow.display();
                            gameBoard.drawPause(gameWindow);
                            gameWindow.display();
                        }
                    }
                    if (debugButton.isClicked(mousex, mousey)) {
                        debugging = !debugging;
                    }
                    if (pauseButton.isClicked(mousex, mousey)){
                        gameBoard.pause();
                        paused = true;
                    }
                }
                else if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    sf::Mouse mouse;
                    int mousex = mouse.getPosition(gameWindow).x;
                    int mousey = mouse.getPosition(gameWindow).y;
                    if ((mousex >= 0 && mousex <= (windowWidth)) &&
                        (mousey >= 0 && mousey <= (num_rows * 32))) {
                        if (!gameBoard.getFlagStatus(mousex, mousey) && !gameBoard.getRevealedStatus(mousex, mousey)) {
                            gameBoard.placeFlag(mousex, mousey);
                            flagCounter.flagPlaced();
                        }
                        else if (gameBoard.getFlagStatus(mousex, mousey) && !gameBoard.getRevealedStatus(mousex, mousey)) {
                            gameBoard.placeFlag(mousex, mousey);
                            flagCounter.flagRemoved();
                        }
                    }
                }
            }
        }
        gameWindow.clear(sf::Color::White);
        smileyButton.drawButton(gameWindow);
        debugButton.drawButton(gameWindow);
        pauseButton.drawButton(gameWindow);
        leaderboardButton.drawButton(gameWindow);
        gameBoard.drawBoard(gameWindow);
        if (debugging){
            gameBoard.drawMines(gameWindow);
        }
        gameBoard.drawFlags(gameWindow);
        flagCounter.drawFlagCounter(gameWindow);
        timeCounter.drawTimeCounter(gameWindow);
        if (gameOver){
            sadfaceButton.drawButton(gameWindow);
            gameBoard.drawMines(gameWindow);
            timeCounter.stopTime();
            sf::Event game_end_event;
            while (gameWindow.pollEvent(game_end_event)){
                if (game_end_event.type == sf::Event::Closed){
                    gameWindow.close();
                    return 0;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Mouse mouse;
                    int mousex = mouse.getPosition(gameWindow).x;
                    int mousey = mouse.getPosition(gameWindow).y;
                    if (sadfaceButton.isClicked(mousex, mousey)) {
                        GameBoard newBoard(num_rows, num_columns, hidden_tile, revealed_tile, flag_texture,
                                           mine_texture,
                                           number_sprite, number_1_texture, number_2_texture, number_3_texture,
                                           number_4_texture,
                                           number_5_texture, number_6_texture, number_7_texture, number_8_texture);
                        newBoard.assignMines(num_mines);
                        newBoard.findZoneValues();
                        gameBoard = newBoard;
                        FlagCounter newFlagCounter(digit_one, digit_two, digit_three, negative, counter, num_mines);
                        newFlagCounter.setPosition(33, ((32 * (num_rows + 0.5)) + 16));
                        flagCounter = newFlagCounter;
                        timeCounter.resetCounter();
                        timeCounter.startTime();
                        smileyButton.drawButton(gameWindow);
                        gameOver = false;
                        break;
                    }
                    if (leaderboardButton.isClicked(mousex, mousey)){
                        sf::RenderWindow leaderboardWindow(sf::VideoMode((num_columns * 16), ((num_rows * 16) + 50)), "Minesweeper");
                        leaderboardWindow.clear(sf::Color::Blue);
                        while (leaderboardWindow.isOpen()){
                            sf::Event event1;
                            while (leaderboardWindow.pollEvent(event1)){
                                if (event1.type == sf::Event::Closed){
                                    leaderboardWindow.close();
                                }
                            }
                            leaderboardWindow.clear(sf::Color::Blue);
                            leaderboardWindow.display();
                        }
                    }
                }

            }
        }
        if (paused){
            gameBoard.drawPause(gameWindow);
            playButton.drawButton(gameWindow);
            timeCounter.stopTime();
            sf::Event pause_event;
            while (gameWindow.pollEvent(pause_event)){
                if (pause_event.type == sf::Event::Closed) {
                    gameWindow.close();
                    return 0;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Mouse mouse;
                    int mousex = mouse.getPosition(gameWindow).x;
                    int mousey = mouse.getPosition(gameWindow).y;
                    if (playButton.isClicked(mousex, mousey)) {
                        paused = false;
                        pauseButton.drawButton(gameWindow);
                        timeCounter.startTime();
                    }
                    if (smileyButton.isClicked(mousex, mousey)) {
                        GameBoard newBoard(num_rows, num_columns, hidden_tile, revealed_tile, flag_texture,
                                           mine_texture,
                                           number_sprite, number_1_texture, number_2_texture, number_3_texture,
                                           number_4_texture,
                                           number_5_texture, number_6_texture, number_7_texture, number_8_texture);
                        newBoard.assignMines(num_mines);
                        newBoard.findZoneValues();
                        gameBoard = newBoard;
                        FlagCounter newFlagCounter(digit_one, digit_two, digit_three, negative, counter, num_mines);
                        newFlagCounter.setPosition(33, ((32 * (num_rows + 0.5)) + 16));
                        flagCounter = newFlagCounter;
                        timeCounter.resetCounter();
                        paused = false;
                    }
                    if (leaderboardButton.isClicked(mousex, mousey)){
                        sf::RenderWindow leaderboardWindow(sf::VideoMode((num_columns * 16), ((num_rows * 16) + 50)), "Minesweeper");
                        leaderboardWindow.clear(sf::Color::Blue);
                        while (leaderboardWindow.isOpen()){
                            sf::Event event1;
                            while (leaderboardWindow.pollEvent(event1)){
                                if (event1.type == sf::Event::Closed){
                                    leaderboardWindow.close();
                                }
                            }
                            leaderboardWindow.clear(sf::Color::Blue);
                            string leader_stats = getStats();
                            displayLeaderboard(leaderboardWidth, leaderboardHeight, leaderboardWindow, welcomeFont, leader_stats);
                            leaderboardWindow.display();
                        }
                    }
                }
            }
        }
        if (gameBoard.checkWin()){
            winfaceButton.drawButton(gameWindow);
            timeCounter.stopTime();

            if (writeToLeader) {
                ofstream leaderboard_file("files/leaderboard.txt", ios::app);
                leaderboard_file << "\n" << timeCounter.getTime() << ", " << user_name << "*";
                writeToLeader = false;
            }

            sf::Event game_end_event;
            while (gameWindow.pollEvent(game_end_event)){
                if (game_end_event.type == sf::Event::Closed){
                    gameWindow.close();
                    return 0;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Mouse mouse;
                    int mousex = mouse.getPosition(gameWindow).x;
                    int mousey = mouse.getPosition(gameWindow).y;
                    if (sadfaceButton.isClicked(mousex, mousey)) {
                        GameBoard newBoard(num_rows, num_columns, hidden_tile, revealed_tile, flag_texture,
                                           mine_texture,
                                           number_sprite, number_1_texture, number_2_texture, number_3_texture,
                                           number_4_texture,
                                           number_5_texture, number_6_texture, number_7_texture, number_8_texture);
                        newBoard.assignMines(num_mines);
                        newBoard.findZoneValues();
                        gameBoard = newBoard;
                        FlagCounter newFlagCounter(digit_one, digit_two, digit_three, negative, counter, num_mines);
                        newFlagCounter.setPosition(33, ((32 * (num_rows + 0.5)) + 16));
                        flagCounter = newFlagCounter;
                        timeCounter.resetCounter();
                        timeCounter.startTime();
                        smileyButton.drawButton(gameWindow);
                        gameOver = false;
                        writeToLeader = true;
                        break;
                    }
                    if (leaderboardButton.isClicked(mousex, mousey)){
                        sf::RenderWindow leaderboardWindow(sf::VideoMode((num_columns * 16), ((num_rows * 16) + 50)), "Minesweeper");
                        leaderboardWindow.clear(sf::Color::Blue);
                        while (leaderboardWindow.isOpen()){
                            sf::Event event1;
                            while (leaderboardWindow.pollEvent(event1)){
                                if (event1.type == sf::Event::Closed){
                                    leaderboardWindow.close();
                                }
                            }
                            leaderboardWindow.clear(sf::Color::Blue);
                            string leader_stats = getStats();
                            displayLeaderboard(leaderboardWidth, leaderboardHeight, leaderboardWindow, welcomeFont, leader_stats);
                            leaderboardWindow.display();
                        }
                    }
                }

            }
        }
        gameWindow.display();
    }


    return 0;
}