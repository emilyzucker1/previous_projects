//
// Created by Emily Zucker on 4/12/24.
//

#ifndef SFML_MINES_H
#define SFML_MINES_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace std;


class Tile{

public:

    Tile(){}

    Tile(sf::Sprite sprite, sf::Sprite number_sprite, sf::Texture revealed_texture, sf::Texture hidden_texture,
         sf::Texture number_1_texture, sf::Texture number_2_texture, sf::Texture number_3_texture,
         sf::Texture number_4_texture, sf::Texture number_5_texture, sf::Texture number_6_texture,
         sf::Texture number_7_texture, sf::Texture number_8_texture, sf::Texture mine_texture){
        tile = sprite;
        tile_number = number_sprite;
        this->hidden_texture = hidden_texture;
        this->revealed_texture = revealed_texture;
        this->number_1_texture = number_1_texture;
        this->number_2_texture = number_2_texture;
        this->number_3_texture = number_3_texture;
        this->number_4_texture = number_4_texture;
        this->number_5_texture = number_5_texture;
        this->number_6_texture = number_6_texture;
        this->number_7_texture = number_7_texture;
        this->number_8_texture = number_8_texture;
        this->mine_texture = mine_texture;
        texture = hidden_texture;
    }

    sf::Sprite getSprite(){
        return tile;
    }

    sf::Vector2f getPosition(){
        return tile.getPosition();
    }

    bool getMarked(){
        return marked;
    }

    bool getRevealed(){
        return revealed;
    }

    void revealTile(){
        texture = revealed_texture;
        tile.setTexture(texture);
        revealed = true;
    }


    void placeFlag(){
        marked = true;
    }

    void removeFlag(){
        marked = false;
    }

    bool isClicked(int mouseX, int mouseY){
        float buttonPosX = tile.getPosition().x;
        float buttonPosY = tile.getPosition().y;

        float buttonPosWidth = buttonPosX + tile.getLocalBounds().width;
        float buttonPosHeight = buttonPosY + tile.getLocalBounds().height;

        if (mouseX < buttonPosWidth && mouseX > buttonPosX
            && mouseY < buttonPosHeight && mouseY > buttonPosY){
            return true;
        }
        else{
            return false;
        }
    }

    void drawTile(sf::RenderWindow &gameWindow, int posX, int posY){
        tile.setTexture(texture);
        tile.setPosition(posX, posY);
        gameWindow.draw(tile);
        if (getRevealed()){
            if (!getMine()) {
                if (zoneValue == 0) {
                    tile_number.setTexture(revealed_texture);
                } else if (zoneValue == 1) {
                    tile_number.setTexture(number_1_texture);
                } else if (zoneValue == 2) {
                    tile_number.setTexture(number_2_texture);
                } else if (zoneValue == 3) {
                    tile_number.setTexture(number_3_texture);
                } else if (zoneValue == 4) {
                    tile_number.setTexture(number_4_texture);
                } else if (zoneValue == 5) {
                    tile_number.setTexture(number_5_texture);
                } else if (zoneValue == 6) {
                    tile_number.setTexture(number_6_texture);
                } else if (zoneValue == 7) {
                    tile_number.setTexture(number_7_texture);
                } else if (zoneValue == 8) {
                    tile_number.setTexture(number_8_texture);
                }
                tile_number.setPosition(posX, posY);
                gameWindow.draw(tile_number);
            }
            else {
                tile_number.setTexture(mine_texture);
                tile_number.setPosition(posX, posY);
                gameWindow.draw(tile_number);
            }
        }
    }

    void assignMine(){
        mine = true;
    }

    bool getMine(){
        return mine;
    }

    void setZoneValue(int value){
        zoneValue = value;
    }

    int getZoneValue(){
        return zoneValue;
    }


private:
    sf::Sprite tile;
    sf::Sprite tile_number;
    sf::Texture hidden_texture;
    sf::Texture revealed_texture;
    sf::Texture texture;
    sf::Texture number_1_texture;
    sf::Texture number_2_texture;
    sf::Texture number_3_texture;
    sf::Texture number_4_texture;
    sf::Texture number_5_texture;
    sf::Texture number_6_texture;
    sf::Texture number_7_texture;
    sf::Texture number_8_texture;
    sf::Texture mine_texture;
    bool mine = false;
    bool revealed = false;
    bool marked = false;
    int zoneValue;

};

class GameBoard{

public:

    GameBoard(){}

    GameBoard(float num_rows, float num_columns, sf::Texture hidden_tile,
              sf::Texture revealed_tile, sf::Texture flag_texture, sf::Texture mine_texture, sf::Sprite number_sprite,
              sf::Texture number_1_texture, sf::Texture number_2_texture, sf::Texture number_3_texture,
              sf::Texture number_4_texture, sf::Texture number_5_texture, sf::Texture number_6_texture,
              sf::Texture number_7_texture, sf::Texture number_8_texture){
        this->hidden_tile = hidden_tile;
        this->revealed_tile = revealed_tile;
        this->flag_texture = flag_texture;
        this->mine_texture = mine_texture;
        this->num_rows = num_rows;
        this->num_columns = num_columns;
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_columns; j++) {
                sf::Sprite tileSprite;
                Tile tile(tileSprite, number_sprite, revealed_tile, hidden_tile, number_1_texture, number_2_texture, number_3_texture,
                          number_4_texture, number_5_texture, number_6_texture, number_7_texture, number_8_texture, mine_texture);
                row.push_back(tile);
            }
            board.push_back(row);
            row.clear();
        }
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_columns; j++) {
                flagRow.push_back(false);
            }
            flagsPlaced.push_back(flagRow);
            flagRow.clear();
        }
    }

    void drawBoard(sf::RenderWindow &gameWindow){
        int xPos = 0;
        int yPos = 0;
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_columns; j++) {
                board.at(i).at(j).drawTile(gameWindow, xPos, yPos);
                sf::FloatRect tileRect = board.at(i).at(j).getSprite().getLocalBounds();
                xPos = xPos + (tileRect.width);
            }
            xPos = 0;
            sf::FloatRect tileRect = board.at(i).at(0).getSprite().getLocalBounds();
            yPos = yPos + (tileRect.height);
        }
    }

    void drawFlags(sf::RenderWindow &gameWindow) {
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (flagsPlaced.at(i).at(j)) {
                    sf::Sprite flag(flag_texture);
                    flag.setPosition(board.at(i).at(j).getPosition());
                    gameWindow.draw(flag);
                }
            }
        }
    }

    void drawMines(sf::RenderWindow &gameWindow){
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (board.at(i).at(j).getMine()) {
                    sf::Sprite mine(mine_texture);
                    mine.setPosition(board.at(i).at(j).getPosition());
                    gameWindow.draw(mine);
                }
            }
        }
    }

    void revealTile(int mousex, int mousey){
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (board.at(i).at(j).isClicked(mousex, mousey)){
                    if (!flagsPlaced.at(i).at(j)){
                        board.at(i).at(j).revealTile();
                        if (board.at(i).at(j).getZoneValue() == 0) {
                            revealNearby(i, j);
                        }
                    }
                }
            }
        }
    }

    void revealNearby(int row_pos, int col_pos){
        if (row_pos == 0){
            if (col_pos == 0){
                if (board.at(row_pos).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                    revealNearby(row_pos, col_pos + 1);
                }
                else if (board.at(row_pos).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                    revealNearby(row_pos + 1, col_pos);
                }
                else if (board.at(row_pos + 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos + 1, col_pos + 1);
                }
                else if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                }
            }
            else if (col_pos == num_columns - 1){
                if (board.at(row_pos).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                    revealNearby(row_pos, col_pos - 1);
                }
                else if (board.at(row_pos).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                     && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                    revealNearby(row_pos + 1, col_pos);
                }
                else if (board.at(row_pos + 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos + 1, col_pos - 1);
                }
                else if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                }
            }
            else{
                if (board.at(row_pos).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                    revealNearby(row_pos, col_pos + 1);
                }
                else if (board.at(row_pos).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                    revealNearby(row_pos, col_pos - 1);
                }
                else if (board.at(row_pos).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                    revealNearby(row_pos + 1, col_pos);
                }
                else if (board.at(row_pos + 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos + 1, col_pos + 1);
                }
                else if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos + 1, col_pos - 1);
                }
                else if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                }
            }
        }
        else if (row_pos == num_rows - 1){
            if (col_pos == 0){
                if (board.at(row_pos).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                    revealNearby(row_pos, col_pos + 1);
                }
                else if (board.at(row_pos).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)) {
                    board.at(row_pos - 1).at(col_pos).revealTile();
                    revealNearby(row_pos - 1, col_pos);
                }
                else if (board.at(row_pos - 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)) {
                    board.at(row_pos - 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos - 1, col_pos + 1);
                }
                else if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                }
            }
            else if (col_pos == num_columns - 1){
                if (board.at(row_pos).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                    revealNearby(row_pos, col_pos - 1);
                }
                else if (board.at(row_pos).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                    revealNearby(row_pos - 1, col_pos);
                }
                else if (board.at(row_pos - 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos - 1, col_pos - 1);
                }
                else if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                }
            }
            else{
                if (board.at(row_pos).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                    revealNearby(row_pos, col_pos + 1);
                }
                else if (board.at(row_pos).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                    revealNearby(row_pos, col_pos - 1);
                }
                else if (board.at(row_pos).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                    revealNearby(row_pos - 1, col_pos);
                }
                else if (board.at(row_pos - 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos - 1, col_pos + 1);
                }
                else if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos - 1, col_pos - 1);
                }
                else if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                }
            }
        }
        else{
            if (col_pos == 0){
                if (board.at(row_pos).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                    revealNearby(row_pos, col_pos + 1);
                }
                else if (board.at(row_pos).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                    revealNearby(row_pos - 1, col_pos);
                }
                else if (board.at(row_pos - 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos - 1, col_pos + 1);
                }
                else if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                    revealNearby(row_pos + 1, col_pos);
                }
                else if (board.at(row_pos + 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos + 1, col_pos + 1);
                }
                else if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                }
            }
            else if (col_pos == num_columns - 1){
                if (board.at(row_pos).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                    revealNearby(row_pos, col_pos - 1);
                }
                else if (board.at(row_pos).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                    revealNearby(row_pos - 1, col_pos);
                }
                else if (board.at(row_pos - 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos - 1, col_pos - 1);
                }
                else if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                    revealNearby(row_pos + 1, col_pos);
                }
                else if (board.at(row_pos + 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos + 1, col_pos - 1);
                }
                else if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                }
            }
            else{
                if (board.at(row_pos).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                    revealNearby(row_pos, col_pos - 1);
                }
                else if (board.at(row_pos).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos - 1)){
                    board.at(row_pos).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                    revealNearby(row_pos, col_pos + 1);
                }
                else if (board.at(row_pos).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos).at(col_pos + 1)){
                    board.at(row_pos).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                    revealNearby(row_pos - 1, col_pos);
                }
                else if (board.at(row_pos - 1).at(col_pos).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos)){
                    board.at(row_pos - 1).at(col_pos).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos - 1, col_pos - 1);
                }
                else if (board.at(row_pos - 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos - 1)){
                    board.at(row_pos - 1).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos - 1, col_pos + 1);
                }
                else if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos)){
                    board.at(row_pos + 1).at(col_pos).revealTile();
                    revealNearby(row_pos + 1, col_pos);
                }
                else if (board.at(row_pos - 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos - 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos - 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos - 1).at(col_pos + 1)){
                    board.at(row_pos - 1).at(col_pos + 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                    revealNearby(row_pos + 1, col_pos - 1);
                }
                else if (board.at(row_pos + 1).at(col_pos - 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos - 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos - 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos - 1)){
                    board.at(row_pos + 1).at(col_pos - 1).revealTile();
                }
                if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() == 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                    revealNearby(row_pos + 1, col_pos + 1);
                }
                else if (board.at(row_pos + 1).at(col_pos + 1).getZoneValue() != 0 && !board.at(row_pos + 1).at(col_pos + 1).getRevealed()
                    && !board.at(row_pos + 1).at(col_pos + 1).getMine() && !flagsPlaced.at(row_pos + 1).at(col_pos + 1)){
                    board.at(row_pos + 1).at(col_pos + 1).revealTile();
                }
            }
        }
    }

    void placeFlag(int mousex, int mousey){
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (board.at(i).at(j).isClicked(mousex, mousey)){
                    if (!board.at(i).at(j).getRevealed()) {
                        board.at(i).at(j).placeFlag();
                        /*flagsPlaced.at(i).at(j) = true;*/
                        flagsPlaced.at(i).at(j) = !flagsPlaced.at(i).at(j);
                    }
                }
            }
        }
    }

    bool getFlagStatus(int mousex, int mousey){
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (board.at(i).at(j).isClicked(mousex, mousey)){
                    return flagsPlaced.at(i).at(j);
                }
            }
        }
        return false;
    }

    bool getMineStatus(int mousex, int mousey){
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (board.at(i).at(j).isClicked(mousex, mousey)){
                    return board.at(i).at(j).getMine();
                }
            }
        }
        return false;
    }

    bool getRevealedStatus(int mousex, int mousey){
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (board.at(i).at(j).isClicked(mousex, mousey)){
                    return board.at(i).at(j).getRevealed();
                }
            }
        }
        return false;
    }

    void assignMines(int num_mines){
        int placed_mines = 0;
        int rand_row = rand() % (int)num_rows;
        int rand_col = rand() % (int)num_columns;
        while (placed_mines < num_mines){
            if (!board.at(rand_row).at(rand_col).getMine()){
                    board.at(rand_row).at(rand_col).assignMine();
                    rand_row = rand() % (int)num_rows;
                    rand_col = rand() % (int)num_columns;
                    placed_mines++;
            }
            else{
                rand_row = rand() % (int)num_rows;
                rand_col = rand() % (int)num_columns;
            }
        }
    }

    void findZoneValues(){
        int num_mines_nearby = 0;
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_columns; j++){
                if (!board.at(i).at(j).getMine()) {
                    if (i == 0) {
                        if (j == 0) {
                            if (board.at(i).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                        else if (j == (num_columns - 1)) {
                            if (board.at(i).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                        else {
                            if (board.at(i).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                    }
                    else if (i == (num_rows - 1)) {
                        if (j == 0) {
                            if (board.at(i).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                        else if (j == (num_columns - 1)) {
                            if (board.at(i).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                        else {
                            if (board.at(i).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                    }
                    else {
                        if (j == 0) {
                            if (board.at(i).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                        else if (j == (num_columns - 1)) {
                            if (board.at(i).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                        else {
                            if (board.at(i).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i - 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j + 1).getMine()) {
                                num_mines_nearby++;
                            }
                            if (board.at(i + 1).at(j - 1).getMine()) {
                                num_mines_nearby++;
                            }
                        }
                    }
                    board.at(i).at(j).setZoneValue(num_mines_nearby);
                    num_mines_nearby = 0;
                }
            }
        }
    }

    bool checkWin(){
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_columns; j++){
                if (!board.at(i).at(j).getRevealed() && !board.at(i).at(j).getMine()){
                    return false;
                }
            }
        }
        return true;
    }

    void pause(){
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_columns; j++){
                sf::Sprite pause_tile(revealed_tile);
                pauseRow.push_back(pause_tile);
            }
            pauseBoard.push_back(pauseRow);
            pauseRow.clear();
        }
    }

    void drawPause(sf::RenderWindow &gameWindow){
        int xPos = 0;
        int yPos = 0;
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_columns; j++) {
                pauseBoard.at(i).at(j).setPosition(xPos, yPos);
                gameWindow.draw(pauseBoard.at(i).at(j));
                sf::FloatRect tileRect = pauseBoard.at(i).at(j).getLocalBounds();
                xPos = xPos + (tileRect.width);
            }
            xPos = 0;
            sf::FloatRect tileRect = pauseBoard.at(i).at(0).getLocalBounds();
            yPos = yPos + (tileRect.height);
        }
    }

private:
    vector<vector<Tile>> board;
    vector<Tile> row;
    vector<vector<sf::Sprite>> pauseBoard;
    vector<sf::Sprite> pauseRow;
    sf::Texture hidden_tile;
    sf::Texture revealed_tile;
    sf::Texture flag_texture;
    sf::Texture mine_texture;
    float num_rows;
    float num_columns;

    vector<vector<bool>> flagsPlaced;
    vector<bool> flagRow;

};

#endif //SFML_MINES_H
