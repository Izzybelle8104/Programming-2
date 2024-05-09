#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifndef PROJECT_3_TILES_H
#define PROJECT_3_TILES_H
class Tiles  {

public:

    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacent_mines;
    sf::Sprite base_sprite;
    sf::Sprite overlay_sprite;
    sf::Sprite tertiary_sprite;
    int col;
    int row;
    vector<Tiles*> adjacent_tiles;
    int number;
    bool isInteractable = true;

    Tiles() : isMine(false), isRevealed(false), isFlagged(false), adjacent_mines(0) {
    }


    void set_base_sprite(sf::Texture* texture_name){
        base_sprite.setTexture(*texture_name);
    }

    void set_overlay_sprite(sf::Texture* texture_name){
        overlay_sprite.setTexture(*texture_name);
    }

    void set_tertiary_sprite(sf::Texture* texture_name){
        tertiary_sprite.setTexture(*texture_name);
    }

    void remove_flag(sf::Texture* texture_name){
        if(!isInteractable) return;
        set_overlay_sprite(texture_name);
        isFlagged = false;
    }
    void set_flag(sf::Texture* texture_name){
        if(!isInteractable) return;
        if(isRevealed) return;

        set_overlay_sprite(texture_name);
        isFlagged = true;
    }



    void reveal_tile(map<string, sf::Texture*>& texturemap){
        if(!isInteractable) return;
        if (isRevealed || isMine || number != 0) {
            isRevealed = true;
            set_base_sprite(texturemap.at("tile_revealed"));
            if(number == 1) set_overlay_sprite(texturemap.at("number_1"));
            if(number == 2) set_overlay_sprite(texturemap.at("number_2"));
            if(number == 3) set_overlay_sprite(texturemap.at("number_3"));
            if(number == 4) set_overlay_sprite(texturemap.at("number_4"));
            if(number == 5) set_overlay_sprite(texturemap.at("number_5"));
            if(number == 6) set_overlay_sprite(texturemap.at("number_6"));
            if(number == 7) set_overlay_sprite(texturemap.at("number_7"));
            if(number == 8) set_overlay_sprite(texturemap.at("number_8"));
            if(isMine) set_tertiary_sprite(texturemap.at("mine"));

            return;
        }

        isRevealed = true;
        set_base_sprite(texturemap.at("tile_revealed"));

        for (auto& tile : adjacent_tiles) {
            //if (tile->number == 0) {
                tile->reveal_tile(texturemap); // Recursive call
            //}
        }
    }

    void bomb_randomizer(vector<vector<Tiles>>& board, int mine_num){
        int bombs = mine_num;
        int counter = 0;
        while (counter < bombs){
            for (int i = 0; i < board.size(); ++i ){
                if(counter == bombs) break;
                int randomRow = rand() % board.size();
                int randomCol = rand() % board[0].size();
                if (board[randomRow][randomCol].isMine == false){
                    board[randomRow][randomCol].isMine = true;
                    counter++;
                }
            }
        }

    }

    void assign_adjacent_tiles(vector<vector<Tiles>>& board, int rows, int columns){
        for(auto& i : board){
            for(auto& j : i){

                //0,0 1,0 2,0
                //0,1 1,1 2,1
                //0,2 1,2 2,2

                // RIGHT
                if (j.col != columns - 1)
                    j.adjacent_tiles.push_back(&board[j.row][j.col + 1]);

                // LEFT
                if (j.col != 0)
                    j.adjacent_tiles.push_back(&board[j.row][j.col - 1]);

                // DOWN
                if (j.row != rows - 1)
                    j.adjacent_tiles.push_back(&board[j.row + 1][j.col]);

                // UP
                if (j.row != 0)
                    j.adjacent_tiles.push_back(&board[j.row - 1][j.col]);

                // UP RIGHT
                if (j.row != 0 && j.col != columns - 1)
                    j.adjacent_tiles.push_back(&board[j.row - 1][j.col + 1]);

                // UP LEFT
                if (j.row != 0 && j.col != 0)
                    j.adjacent_tiles.push_back(&board[j.row - 1][j.col - 1]);

                // DOWN RIGHT
                if (j.row != rows - 1 && j.col != columns - 1)
                    j.adjacent_tiles.push_back(&board[j.row + 1][j.col + 1]);

                // DOWN LEFT
                if (j.row != rows - 1 && j.col != 0)
                    j.adjacent_tiles.push_back(&board[j.row + 1][j.col - 1]);
            }
        }
    }
    void assign_mine_num(){
        int counter = 0;
        for(auto i : adjacent_tiles){
            if(i->isMine) counter++;
        }

        number = counter;
    }


};

#endif //PROJECT_3_TILES_H
