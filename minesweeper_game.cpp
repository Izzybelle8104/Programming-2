#include <iostream>
#include <map>
#include <vector>
#include <cctype>
#include <string>
#include <chrono>
#include <SFML/Graphics.hpp>


#include "Tiles.h"
#include "Buttons.h"
#include "Data.h"

using namespace std;

class MindSweeper_Game {
private:
    Data data;
    Tiles tiles;
    vector<vector<Tiles>> board;
    bool isDebug = false;
    bool isPaused = false;
    bool isNegativeCounter = false;
    int time;
    string name;
    bool isGameOver = false;
    int seconds_paused = 0;
    bool display_leaderboard = false;

public:
    MindSweeper_Game(Data& data, Tiles tiles) {
        this->data = data;
        this->tiles = tiles;
    }


//HeELPER FUNCTIONS -----------------------------------------------------------------------------------------------------------

    //Board Data -------------------------------------------------------------------------------------------------------

    void make_tiles(map<string,sf::Texture*>& my_textures){
        for (int i = 0; i < data.rows; ++i) {
            vector<Tiles> row_tiles;
            for (int j = 0; j < data.columns; ++j) {
                Tiles tile;
                tile.set_base_sprite(my_textures.at("tile_hidden"));
                tile.set_overlay_sprite(my_textures.at("null"));
                tile.set_tertiary_sprite(my_textures.at("null"));
                //adjusting position
                tile.base_sprite.setPosition(j * data.tile_width, i * data.tile_height);
                tile.overlay_sprite.setPosition(j * data.tile_width, i * data.tile_height);
                tile.tertiary_sprite.setPosition(j * data.tile_width, i * data.tile_height);
                tile.col = j;
                tile.row = i;
                row_tiles.push_back(tile);
            }
            board.push_back(row_tiles);
        }

        tiles.assign_adjacent_tiles(board, data.rows, data.columns);

        tiles.bomb_randomizer(board, data.mine_num);

        for(auto& i : board){
            for(auto& j : i){
                j.assign_mine_num();
            }
        }
    }

    void UpdateGameTimer(int& display_seconds, int& timer_elapsed_seconds, std::chrono::steady_clock::time_point& start_time,
                         sf::Sprite& timer_sprite_one_sec, sf::Sprite& timer_sprite_ten_sec, sf::Sprite& timer_sprite_one_min,
                         sf::Sprite& timer_sprite_ten_min){

        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
        if (elapsed_seconds.count() % 1 == 0 and elapsed_seconds.count() != timer_elapsed_seconds) {

            timer_elapsed_seconds = elapsed_seconds.count();
            if(isPaused){
                seconds_paused++;
                return;
            }
            timer_elapsed_seconds -= seconds_paused;
            time = timer_elapsed_seconds;

            display_seconds = timer_elapsed_seconds % 60;
            if(display_seconds % 60 == 0) display_seconds = 0;
            if(display_seconds % 10 == 0) timer_sprite_one_sec.setTextureRect(sf::IntRect(0, 0, 21, 32));
            if(display_seconds % 10 == 1) timer_sprite_one_sec.setTextureRect(sf::IntRect(21, 0, 21, 32));
            if(display_seconds % 10 == 2) timer_sprite_one_sec.setTextureRect(sf::IntRect(42, 0, 21, 32));
            if(display_seconds % 10 == 3) timer_sprite_one_sec.setTextureRect(sf::IntRect(63, 0, 21, 32));
            if(display_seconds % 10 == 4) timer_sprite_one_sec.setTextureRect(sf::IntRect(84, 0, 21, 32));
            if(display_seconds % 10 == 5) timer_sprite_one_sec.setTextureRect(sf::IntRect(105, 0, 21, 32));
            if(display_seconds % 10 == 6) timer_sprite_one_sec.setTextureRect(sf::IntRect(126, 0, 21, 32));
            if(display_seconds % 10 == 7) timer_sprite_one_sec.setTextureRect(sf::IntRect(147, 0, 21, 32));
            if(display_seconds % 10 == 8) timer_sprite_one_sec.setTextureRect(sf::IntRect(168, 0, 21, 32));
            if(display_seconds % 10 == 9) timer_sprite_one_sec.setTextureRect(sf::IntRect(189, 0, 21, 32));

            if((display_seconds/10) % 10 == 0) timer_sprite_ten_sec.setTextureRect(sf::IntRect(0, 0, 21, 32));
            if((display_seconds/10) % 10 == 1) timer_sprite_ten_sec.setTextureRect(sf::IntRect(21, 0, 21, 32));
            if((display_seconds/10) % 10 == 2) timer_sprite_ten_sec.setTextureRect(sf::IntRect(42, 0, 21, 32));
            if((display_seconds/10) % 10 == 3) timer_sprite_ten_sec.setTextureRect(sf::IntRect(63, 0, 21, 32));
            if((display_seconds/10) % 10 == 4) timer_sprite_ten_sec.setTextureRect(sf::IntRect(84, 0, 21, 32));
            if((display_seconds/10) % 10 == 5) timer_sprite_ten_sec.setTextureRect(sf::IntRect(105, 0, 21, 32));
            if((display_seconds/10) % 10 == 6) timer_sprite_ten_sec.setTextureRect(sf::IntRect(126, 0, 21, 32));
            if((display_seconds/10) % 10 == 7) timer_sprite_ten_sec.setTextureRect(sf::IntRect(147, 0, 21, 32));
            if((display_seconds/10) % 10 == 8) timer_sprite_ten_sec.setTextureRect(sf::IntRect(168, 0, 21, 32));
            if((display_seconds/10) % 10 == 9) timer_sprite_ten_sec.setTextureRect(sf::IntRect(189, 0, 21, 32));

            int total_minutes = (timer_elapsed_seconds/60);
            if(total_minutes % 10 == 0) timer_sprite_one_min.setTextureRect(sf::IntRect(0, 0, 21, 32));
            if(total_minutes % 10 == 1) timer_sprite_one_min.setTextureRect(sf::IntRect(21, 0, 21, 32));
            if(total_minutes % 10 == 2) timer_sprite_one_min.setTextureRect(sf::IntRect(42, 0, 21, 32));
            if(total_minutes % 10 == 3) timer_sprite_one_min.setTextureRect(sf::IntRect(63, 0, 21, 32));
            if(total_minutes % 10 == 4) timer_sprite_one_min.setTextureRect(sf::IntRect(84, 0, 21, 32));
            if(total_minutes % 10 == 5) timer_sprite_one_min.setTextureRect(sf::IntRect(105, 0, 21, 32));
            if(total_minutes % 10 == 6) timer_sprite_one_min.setTextureRect(sf::IntRect(126, 0, 21, 32));
            if(total_minutes % 10 == 7) timer_sprite_one_min.setTextureRect(sf::IntRect(147, 0, 21, 32));
            if(total_minutes % 10 == 8) timer_sprite_one_min.setTextureRect(sf::IntRect(168, 0, 21, 32));
            if(total_minutes % 10 == 9) timer_sprite_one_min.setTextureRect(sf::IntRect(189, 0, 21, 32));

            if((total_minutes/10) % 10 == 0) timer_sprite_ten_min.setTextureRect(sf::IntRect(0, 0, 21, 32));
            if((total_minutes/10) % 10 == 1) timer_sprite_ten_min.setTextureRect(sf::IntRect(21, 0, 21, 32));
            if((total_minutes/10) % 10 == 2) timer_sprite_ten_min.setTextureRect(sf::IntRect(42, 0, 21, 32));
            if((total_minutes/10) % 10 == 3) timer_sprite_ten_min.setTextureRect(sf::IntRect(63, 0, 21, 32));
            if((total_minutes/10) % 10 == 4) timer_sprite_ten_min.setTextureRect(sf::IntRect(84, 0, 21, 32));
            if((total_minutes/10) % 10 == 5) timer_sprite_ten_min.setTextureRect(sf::IntRect(105, 0, 21, 32));
            if((total_minutes/10) % 10 == 6) timer_sprite_ten_min.setTextureRect(sf::IntRect(126, 0, 21, 32));
            if((total_minutes/10) % 10 == 7) timer_sprite_ten_min.setTextureRect(sf::IntRect(147, 0, 21, 32));
            if((total_minutes/10) % 10 == 8) timer_sprite_ten_min.setTextureRect(sf::IntRect(168, 0, 21, 32));
            if((total_minutes/10) % 10 == 9) timer_sprite_ten_min.setTextureRect(sf::IntRect(189, 0, 21, 32));
        }
    }

    int GetBoardFlagAmount(){
        int counter = 0;
        for(auto i : board){
            for(auto j : i){
                if(j.isFlagged) counter++;
            }
        }

        return counter;
    }

    void UpdateGameCounter(sf::Sprite& counter_ones, sf::Sprite& counter_tenths, sf::Sprite& counter_hundreds){
        int flags = GetBoardFlagAmount();
        int bomb_count = data.mine_num;

        int counter = bomb_count - flags;
        if(counter < 0) isNegativeCounter = true;
        else isNegativeCounter = false;

        if(isNegativeCounter) counter *= -1;
        counter_ones.setTextureRect(sf::IntRect((counter % 10) * 21, 0, 21, 32));
        counter_tenths.setTextureRect(sf::IntRect(((counter / 10) % 10) * 21, 0, 21, 32));
        counter_hundreds.setTextureRect(sf::IntRect(((counter / 100) % 10) * 21, 0, 21, 32));

    }

    void RightMouseInteractions(sf::Event& game_event, map<string, sf::Texture*>& my_textures){
        for (auto &i: board) {
            for (auto &j: i) {
                if (j.base_sprite.getGlobalBounds().contains(game_event.mouseButton.x, game_event.mouseButton.y)) {
                    if(j.isFlagged) j.remove_flag(my_textures.at("null"));
                    else j.set_flag(my_textures.at("flag"));
                }
            }
        }
    }

    void LeftMouseInteractions(sf::Event& game_event, map<string, sf::Texture*>& my_textures, Button& debug, Button& play, Button& leaderboard, sf::Font &my_font, sf::RenderWindow& game_window, Button& face){
        for (auto &i: board) {
            for (auto &j: i) {
                if (j.base_sprite.getGlobalBounds().contains(game_event.mouseButton.x,
                                                             game_event.mouseButton.y)) {
                    j.reveal_tile(my_textures);
                }
            }
        }

        if(debug.get_button().getGlobalBounds().contains(game_event.mouseButton.x,game_event.mouseButton.y)){
            if(!debug.isEnabled) return;
            isDebug = !isDebug;
            ShowMines(isDebug, my_textures);
        }

        if(leaderboard.get_button().getGlobalBounds().contains(game_event.mouseButton.x,game_event.mouseButton.y)){
            if(!isGameOver)PauseGame(my_textures);
            debug.isEnabled = !debug.isEnabled;
            face.isEnabled = !face.isEnabled;
            play.isEnabled = !play.isEnabled;

            display_leaderboard = true;
        }

        if(play.get_button().getGlobalBounds().contains(game_event.mouseButton.x,game_event.mouseButton.y)){
            if(!isGameOver) PauseGame(my_textures);
            debug.isEnabled = !debug.isEnabled;
        }
    }

    void PauseGame(map<string,sf::Texture*>& my_textures){
        isPaused = !isPaused;
        for (auto &i: board) {
            for (auto &j: i) {
               j.isInteractable = !j.isInteractable;
            }
        }

        if(isPaused){

            for(auto& i : board){
                for(auto& j : i){
                    j.set_base_sprite(my_textures.at("tile_revealed"));
                    j.set_overlay_sprite(my_textures.at("null"));
                }
            }
        }
        if(!isPaused){

            for(auto& i : board){
                for(auto& j : i){
                    if(j.isRevealed) j.set_base_sprite(my_textures.at("tile_revealed"));
                    else j.set_base_sprite(my_textures.at("tile_hidden"));

                    if(j.isFlagged)j.set_overlay_sprite(my_textures.at("flag"));
                    if(j.isRevealed) j.reveal_tile(my_textures);

                }
            }
        }
    }
    void ShowMines(bool show, map<string, sf::Texture*>& my_textures){
        for(auto& i : board){
            for(auto& j : i){
                if(show)
                    if(j.isMine) j.set_tertiary_sprite(my_textures.at("mine"));
                if(!show){
                    if(j.isMine && !j.isRevealed) j.set_tertiary_sprite(my_textures.at("null"));
                }
            }
        }
    }

    bool IsGameOver(){
        for(auto& i : board){
            for(auto& j : i){
                if(j.isRevealed && j.isMine){
                    return true;
                }
            }
        }

        for(auto& i : board){
            for(auto& j : i){
                if(j.isMine && !j.isFlagged){
                    return false;
                }
            }
        }

        for(auto& i : board){
            for(auto& j : i){
                if(!j.isRevealed && !j.isMine){
                    return false;
                }
            }
        }

        return true;
    }
    bool IsWin(){
        for(auto& i : board){
            for(auto& j : i){
                if(j.isRevealed && j.isMine){
                    return false;
                }
            }
        }
        return true;
    }

    void GameOver(map<string, sf::Texture*>& my_textures, Button& face){
        isGameOver = true;
        PauseGame(my_textures);
        ShowMines(true, my_textures);
        for(auto& i : board){
            for(auto& j : i){
                j.isInteractable = false;
            }
        }

        if(!IsWin()) face.set_sprite(my_textures.at("face_lose"));
        else face.set_sprite(my_textures.at("face_win"));

        if(IsWin()){
            Data::Player player;
            player.name = name;
            player.time_val = time;


            string mins_one;
            string mins_ten;
            string sec_one;
            string sec_ten;

            int minutes = time / 60;
            int mins_one_digit = minutes % 10;
            int mins_ten_digit = (minutes / 10) % 10;
            int seconds = time % 60;
            int sec_one_digit = seconds % 10;
            int sec_ten_digit = (seconds / 10) % 10;

// Convert digits to characters
            mins_one = to_string(mins_one_digit);
            mins_ten = to_string(mins_ten_digit);
            sec_one = to_string(sec_one_digit);
            sec_ten = to_string(sec_ten_digit);

// Construct the string representation of time
            player.time = mins_ten + mins_one + ":" + sec_ten + sec_one;

// Output the constructed time string

            data.leaderboard_info.push_back(player);
            data.bubble_sort();
            data.write_leaderboard();

        }

    }

//WINDOWS --------------------------------------------------------------------------------------------------------------

    //welcome_window --------------------------------------------------------------------------------------------------
    string welcome_window(sf::Font &my_font) {
        sf::RenderWindow welcome_window(sf::VideoMode(data.windows_width, data.windows_height), "Welcome Window",
                                        sf::Style::Close);

        //Welcome text -------------------------------------------------------------------------------------------------
        sf::Text welcome_text("WELCOME TO MINESWEEPER!", my_font, 24);
        welcome_text.setFillColor(sf::Color::White);
        welcome_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

        sf::FloatRect textRect_wt = welcome_text.getGlobalBounds();
        welcome_text.setOrigin(textRect_wt.left + textRect_wt.width / 2.0f,
                               textRect_wt.top + textRect_wt.height / 2.0f);
        welcome_text.setPosition(sf::Vector2f(data.welcome_text_alignment_x, data.welcome_text_alignment_y));

        //Name label ---------------------------------------------------------------------------------------------------
        sf::Text name_label("Enter your name:", my_font, 20);
        name_label.setFillColor(sf::Color::White);
        name_label.setStyle(sf::Text::Bold);

        sf::FloatRect textRect_nl = name_label.getGlobalBounds();
        name_label.setOrigin(textRect_nl.left + textRect_nl.width / 2.0f,
                             textRect_nl.top + textRect_nl.height / 2.0f);
        name_label.setPosition(sf::Vector2f(data.enter_name_text_alignment_x, data.enter_name_text_alignment_y));

        //Input name ---------------------------------------------------------------------------------------------------
        sf::Text name_text;
        name_text.setFont(my_font);
        name_text.setString("|");
        name_text.setFillColor(sf::Color::Yellow);
        name_text.setStyle(sf::Text::Bold);
        name_text.setCharacterSize(18);

        sf::FloatRect textRect_nt = name_text.getGlobalBounds();
        name_text.setOrigin(textRect_nt.left + textRect_nt.width / 2.0f,
                            textRect_nt.top + textRect_nt.height / 2.0f);
        name_text.setPosition(sf::Vector2f(data.typed_name_alignment_x, data.typed_name_alignment_y));

        //Event --------------------------------------------------------------------------------------------------------
        string name_input = "";

        while (welcome_window.isOpen()) {
            sf::Event welcome_event;
            while (welcome_window.pollEvent(welcome_event)) {
                if (welcome_event.type == sf::Event::Closed) {
                    welcome_window.close();
                } else if (welcome_event.type == sf::Event::TextEntered) {
                    //check if the first key is backspace
                    if (welcome_event.text.unicode == '\b') {
                        if (!name_input.empty()) {
                            name_input.pop_back();
                        }
                    }
                        //check for valid characters
                    else if ((welcome_event.text.unicode >= 65 and welcome_event.text.unicode <= 90) or
                             (welcome_event.text.unicode >= 97 and welcome_event.text.unicode <= 122)) {
                        if (name_input.size() < 10) {
                            name_input += static_cast<char>(welcome_event.text.unicode);
                        }
                    }
                    //after checking now we capitalize and lowercase the letters and display the cursor
                    if (!name_input.empty()) {
                        name_input[0] = toupper((name_input[0]));
                        for (int i = 1; i < name_input.size(); ++i) {
                            name_input[i] = tolower(name_input[i]);
                        }
                    }

                    name_text.setString(name_input + '|');

                    //recenter
                    sf::FloatRect textRect_recenter = name_text.getLocalBounds();
                    float textWidth = textRect_recenter.width;
                    name_text.setOrigin(textWidth / 2, textRect_recenter.height / 2);
                    name_text.setPosition(data.typed_name_alignment_x, data.typed_name_alignment_y);

                }
                //check if we can exit the window
                if (welcome_event.type == sf::Event::KeyPressed && welcome_event.key.code == sf::Keyboard::Enter) {
                    if (!name_input.empty()) {
                        welcome_window.close();
//                        string str = name_text.getString().toAnsiString();
//                        str.pop_back();
                        return name_input;
                    }
                }

            }

            welcome_window.clear(sf::Color::Blue);
            welcome_window.draw(welcome_text);
            welcome_window.draw(name_label);
            welcome_window.draw(name_text);
            welcome_window.display();
        }


    }

    //game_window -----------------------------------------------------------------------------------------------
    bool game_window(map<string,sf::Texture*>& my_textures, string name, sf::Font &my_font) {
        this->name = name;

        sf::RenderWindow game_window(sf::VideoMode(data.windows_width, data.windows_height), "Welcome Window",
                                     sf::Style::Close);

        auto start_time = std::chrono::steady_clock::now();
        //tiles
        make_tiles(my_textures);
        //display bomb sprite if mine_num true



        //face
        float face_pos_x = (((data.columns / 2.0) * 32) - 32);
        float face_pos_y = ((data.rows + 0.5) * 32);

        Button face(my_textures.at("face_happy"), face_pos_x, face_pos_y);
        Button face_win(my_textures.at("face_win"), face_pos_x, face_pos_y);
        Button face_lose(my_textures.at("face_lose"), face_pos_x, face_pos_y);

        //debug
        float debug_pos_x = ((data.columns * 32) - 304);
        float debug_pos_y = ((data.rows + 0.5) * 32);

        Button debug(my_textures.at("debug"), debug_pos_x, debug_pos_y );

        //pause/play
        float pause_pos_x = ((data.columns * 32) - 240);
        float pause_pos_y = ((data.rows + 0.5) * 32);

        Button pause(my_textures.at("pause"), pause_pos_x, pause_pos_y);
        Button play(my_textures.at("play"), pause_pos_x, pause_pos_y);

        //leaderboard button
        float lb_pos_x = ((data.columns * 32) - 176);
        float lb_pos_y = ((data.rows + 0.5) * 32);

        Button leaderboard(my_textures.at("leaderboard"), lb_pos_x, lb_pos_y);

        //Timer
        float time_min_x = ((data.columns * 32) - 97);
        float time_min_y = ((data.rows + 0.5) * 32 + 16);

        float time_sec_x = ((data.columns * 32) - 54);
        float time_sec_y = ((data.rows + 0.5) * 32 + 16);

        sf::Sprite timer_sprite_one_sec;
        timer_sprite_one_sec.setTexture(*my_textures.at("digits"));
        timer_sprite_one_sec.setTextureRect(sf::IntRect(0, 0, 21, 32));
        timer_sprite_one_sec.setPosition(time_sec_x + 21, time_sec_y);

        sf::Sprite timer_sprite_ten_sec;
        timer_sprite_ten_sec.setTexture(*my_textures.at("digits"));
        timer_sprite_ten_sec.setTextureRect(sf::IntRect(0, 0, 21, 32));
        timer_sprite_ten_sec.setPosition(time_sec_x, time_sec_y);

        sf::Sprite timer_sprite_one_min;
        timer_sprite_one_min.setTexture(*my_textures.at("digits"));
        timer_sprite_one_min.setTextureRect(sf::IntRect(0, 0, 21, 32));
        timer_sprite_one_min.setPosition(time_min_x + 21, time_min_y);

        sf::Sprite timer_sprite_ten_min;
        timer_sprite_ten_min.setTexture(*my_textures.at("digits"));
        timer_sprite_ten_min.setTextureRect(sf::IntRect(0, 0, 21, 32));
        timer_sprite_ten_min.setPosition(time_min_x, time_min_y);


        //counter
        float counter_x = 33;
        float counter_y = ((data.rows + 0.5) * 32 + 16);

        sf::Sprite counter_sign;
        counter_sign.setTexture(*my_textures.at("digits"));
        counter_sign.setTextureRect(sf::IntRect(210, 0, 21, 32));
        counter_sign.setPosition(12, 32 * (data.rows + .5) + 16);

        sf::Sprite counter_hundreds;
        counter_hundreds.setTexture(*my_textures.at("digits"));
        counter_hundreds.setTextureRect(sf::IntRect(0, 0, 21, 32));
        counter_hundreds.setPosition(counter_x, counter_y);

        sf::Sprite counter_tenths;
        counter_tenths.setTexture(*my_textures.at("digits"));
        counter_tenths.setTextureRect(sf::IntRect(0, 0, 21, 32));
        counter_tenths.setPosition(counter_x + 21, counter_y);

        sf::Sprite counter_ones;
        counter_ones.setTexture(*my_textures.at("digits"));
        counter_ones.setTextureRect(sf::IntRect(0, 0, 21, 32));
        counter_ones.setPosition(counter_x + 42, counter_y);

        UpdateGameCounter(counter_ones,counter_tenths, counter_hundreds);
        //Run window

        int timer_elapsed_seconds = 0;
        int display_seconds = 0;

        while (game_window.isOpen()) {
            if(display_leaderboard){
                leaderboard_window(my_font, my_textures);
                display_leaderboard = false;
                if(!isGameOver) PauseGame(my_textures);
                debug.isEnabled = !debug.isEnabled;
                face.isEnabled = !face.isEnabled;
                play.isEnabled = !play.isEnabled;
            }

            sf::Event game_event;
            while (game_window.pollEvent(game_event)) {
                if (game_event.type == sf::Event::Closed) {
                    game_window.close();
                }

                if(game_event.type == sf::Event::MouseButtonPressed){
                    if(face.get_button().getGlobalBounds().contains(game_event.mouseButton.x,game_event.mouseButton.y)){
                        if(face.isEnabled)
                        return true;
                    }

                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        RightMouseInteractions(game_event, my_textures);
                        UpdateGameCounter(counter_ones,counter_tenths, counter_hundreds);
                    }
                    else {
                        LeftMouseInteractions(game_event, my_textures, debug, play, leaderboard, my_font, game_window, face);
                    }
                }

                if(!isGameOver) if(IsGameOver()) GameOver(my_textures, face);
            }



            //Timer -------------------------------------------------------------------------------------------------------

            UpdateGameTimer(display_seconds, timer_elapsed_seconds, start_time,timer_sprite_one_sec, timer_sprite_ten_sec,
                            timer_sprite_one_min,timer_sprite_ten_min);

            //Run

            game_window.clear(sf::Color::White);

            //display buttons and such
            for (int i = 0; i < data.rows; ++i) {
                // Iterate over each column in the current row
                for (int j = 0; j < data.columns; ++j) {
                    game_window.draw(board[i][j].base_sprite);
                    if(board[i][j].overlay_sprite.getTexture() != my_textures.at("null")) {
                        game_window.draw(board[i][j].overlay_sprite);
                    }
                    if(board[i][j].tertiary_sprite.getTexture() != my_textures.at("null")) {
                        game_window.draw(board[i][j].tertiary_sprite);
                    }
                }
            }



            if(isNegativeCounter) game_window.draw(counter_sign);
            if(isPaused) play.set_sprite(my_textures.at("pause"));
            else{play.set_sprite(my_textures.at("play"));}
            game_window.draw(face.get_button());
            game_window.draw(play.get_button());
            game_window.draw(debug.get_button());
            game_window.draw(leaderboard.get_button());
            game_window.draw(timer_sprite_one_sec);
            game_window.draw(timer_sprite_ten_sec);
            game_window.draw(timer_sprite_one_min);
            game_window.draw(timer_sprite_ten_min);
            game_window.draw(counter_hundreds);
            game_window.draw(counter_tenths);
            game_window.draw(counter_ones);


            game_window.display();

        }
    }

    void leaderboard_window(sf::Font &my_font, map<string,sf::Texture*>& my_textures){
        sf::RenderWindow lb_window(sf::VideoMode(data.leaderboard_width, data.leaderboard_height), "Welcome Window",
                                   sf::Style::Close);

        auto start_time = std::chrono::steady_clock::now();

        //Leardboard text -------------------------------------------------------------------------------------------------
        sf::Text lb_text("LEADERBOARD", my_font, 20);
        lb_text.setFillColor(sf::Color::White);
        lb_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

        sf::FloatRect textRect_lbt = lb_text.getGlobalBounds();
        lb_text.setOrigin(textRect_lbt.left + textRect_lbt.width / 2.0f,
                          textRect_lbt.top + textRect_lbt.height / 2.0f);
        lb_text.setPosition(sf::Vector2f(data.leaderboard_title_x,data.leaderboard_title_y));

        //display names
        string player_1 = "1.\t" + data.leaderboard_info[0].time + '\t' + data.leaderboard_info[0].name;
        string player_2 = "2.\t" + data.leaderboard_info[1].time + '\t' + data.leaderboard_info[1].name;
        string player_3 = "3.\t" + data.leaderboard_info[2].time + '\t' + data.leaderboard_info[2].name;
        string player_4 = "4.\t" + data.leaderboard_info[3].time + '\t' + data.leaderboard_info[3].name;
        string player_5 = "5.\t" + data.leaderboard_info[4].time + '\t' + data.leaderboard_info[4].name;

        string pl1 = "";
        string pl2 = "";
        string pl3 = "";
        string pl4 = "";
        string pl5 = "";
        if(data.leaderboard_info[0].name == name) pl1 = "*";
        if(data.leaderboard_info[1].name == name) pl2 = "*";
        if(data.leaderboard_info[2].name == name) pl3 = "*";
        if(data.leaderboard_info[3].name == name) pl4 = "*";
        if(data.leaderboard_info[4].name == name) pl5 = "*";
        string all_players = player_1 + pl1 + "\n\n" + player_2 + pl2+ "\n\n" + player_3 + pl3 + "\n\n" + player_4 + pl4 + "\n\n" + player_5 + pl5 + "\n\n";



        sf::Text players(all_players, my_font, 18);
        players.setFillColor(sf::Color::White);
        players.setStyle(sf::Text::Bold);

        sf::FloatRect textRect_players = players.getGlobalBounds();
        players.setOrigin(textRect_players.left + textRect_players.width / 2.0f,
                          textRect_players.top + textRect_players.height / 2.0f);
        players.setPosition(sf::Vector2f(data.content_leadershipboard_x,data.content_leadershipboard_y));

        while (lb_window.isOpen()) {
            sf::Event lb_event;
            while (lb_window.pollEvent(lb_event)) {
                if (lb_event.type == sf::Event::Closed) {
                    auto current_time = std::chrono::steady_clock::now();
                    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
                    int timer_elapsed_seconds = elapsed_seconds.count();
                    seconds_paused += timer_elapsed_seconds;
                    lb_window.close();
                }
            }
            lb_window.clear(sf::Color::Blue);
            lb_window.draw(lb_text);
            lb_window.draw(players);
            lb_window.display();
        }
    }

};


int main() {

//LOAD DATA ------------------------------------------------------------------------------------------------------------
    //variables
    Data data;

    Tiles tile;

    data.read_config();

    data.read_imagedata(data.filePaths);

    data.read_leadershipboard();



    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        std::cerr << "Failed to load font file" << std::endl;
        return 1;
    }

//RUN GAME -------------------------------------------------------------------------------------------------------------

    bool restartGame = true;
    bool welcome_window = true;
    string name;

    while (restartGame) {
        MindSweeper_Game mindsweeper(data,tile);
        //welcome window
        if(welcome_window) name = mindsweeper.welcome_window(font);
        restartGame = mindsweeper.game_window(data.get_textures(), name, font);
        if(restartGame) welcome_window = false;

    }

    return 0;
};
