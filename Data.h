#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

#ifndef PROJECT_3_DATA_H
#define PROJECT_3_DATA_H

class Data {
private:
    map<string, sf::Texture*> texturemap;

public:
    Data()= default;

    //dimensions
    int columns;
    int rows;
    int dimensions;

    //welcome_window
    float windows_height;
    float windows_width;

    //text positioning
    float welcome_text_alignment_x;
    float welcome_text_alignment_y;
    float enter_name_text_alignment_x;
    float enter_name_text_alignment_y;
    float typed_name_alignment_x;
    float typed_name_alignment_y;


    //leadership window
    float leaderboard_height;
    float leaderboard_width;

    //text positioning
    float leaderboard_title_x;
    float leaderboard_title_y;
    float content_leadershipboard_x;
    float content_leadershipboard_y;

    //tiles
    int tile_width;
    int tile_height;

    //other
    int mine_num;

    //filepaths
    vector <string> filePaths = {
            "../files/images/number_1.png",
            "../files/images/number_2.png",
            "../files/images/number_3.png",
            "../files/images/number_4.png",
            "../files/images/number_5.png",
            "../files/images/number_6.png",
            "../files/images/number_7.png",
            "../files/images/number_8.png",
            "../files/images/pause.png",
            "../files/images/play.png",
            "../files/images/tile_hidden.png",
            "../files/images/tile_revealed.png",
            "../files/images/debug.png",
            "../files/images/digits.png",
            "../files/images/face_happy.png",
            "../files/images/face_lose.png",
            "../files/images/face_win.png",
            "../files/images/flag.png",
            "../files/images/leaderboard.png",
            "../files/images/mine.png",
            "../files/images/null.png"
    };

    //Leadership board
    struct Player{
        string name;
        string time;
        int time_val;
    };

    vector<Player> leaderboard_info;

//READ DATA ------------------------------------------------------------------------------------------------------------

    //CONFIGURE FILE ---------------------------------------------------------------------------------------------------
    void read_config() {
        ifstream config("../files/config.cfg");
        if (!config.is_open()) {
            cerr << "Failed to open the file" << endl;
            return;
        }

        if (!(config >> columns >> rows >> mine_num)) {
            std::cerr << "Failed to read values from config file" << std::endl;
            return;
        }

        //windows variable initializations -----------------------------------------------------------------------------
        windows_height = ((rows * 32) + 100);
        windows_width = (columns * 32);
        dimensions = (rows * columns);

        //welcome_window -----------------------------------------------------------------------------------------------
        welcome_text_alignment_x = (windows_width / 2);
        welcome_text_alignment_y = ((windows_height / 2) - 150);
        enter_name_text_alignment_x = (windows_width / 2);
        enter_name_text_alignment_y = ((windows_height / 2) - 75);
        typed_name_alignment_x = (windows_width / 2);
        typed_name_alignment_y = ((windows_height / 2) - 45);

        //leadership board window --------------------------------------------------------------------------------------

        leaderboard_height = ((rows * 16) + 50);
        leaderboard_width = (columns * 16);

        leaderboard_title_x = (leaderboard_width / 2);
        leaderboard_title_y = ((leaderboard_height / 2) - 120);
        content_leadershipboard_x = (leaderboard_width / 2);
        content_leadershipboard_y = ((leaderboard_height / 2) + 20);


        //tiles
        tile_width = windows_width / columns;
        tile_height = (windows_height - 100) / rows;

        config.close();
    }

    //LEADERSHIP BOARD -------------------------------------------------------------------------------------------------
    void read_leadershipboard() {
        ifstream leadership_file("../files/leaderboard.txt");
        if (!leadership_file.is_open()) {
            cerr << "Failed to open leaderboard file: " << endl;
            return;
        }

        Player player;
        while (leadership_file >> player.time >> player.name) {
            player.time = player.time.erase(player.time.size() - 1);
            leaderboard_info.push_back(player);
        }
        for (int i = 0; i < leaderboard_info.size(); ++i){
            string chars = leaderboard_info[i].time;
            int min_val = stoi(chars.substr(0, 2));
            int sec_val = stoi(chars.substr(3, 2));
            leaderboard_info[i].time_val = min_val * 60 + sec_val;
        }
    }


    bool isSorted(){
        for(int i = 0; i < leaderboard_info.size() - 1; i++){
            if(leaderboard_info[i].time_val > leaderboard_info[i+1].time_val) return false;
        }

        return true;
    }

    void write_leaderboard(){
        ofstream outfile("../files/leaderboard.txt");
        if (!outfile) {
            cerr << "Error: Unable to open file." << endl;
            return;
        }

        for (const Player& player : leaderboard_info) {
            int minutes = player.time_val / 60;
            int seconds = player.time_val % 60;
            outfile << setw(2) << setfill('0') << minutes << ":"
                    << setw(2) << setfill('0') << seconds << ", "
                    << player.name << endl;
        }

        outfile.close();
    }

    void bubble_sort(){
        while(!isSorted()){
            for(int i = 0; i < leaderboard_info.size() - 1; i++){
                if(leaderboard_info[i].time_val > leaderboard_info[i+1].time_val){
                    Player temp = leaderboard_info[i];
                    leaderboard_info[i] = leaderboard_info[i+1];
                    leaderboard_info[i + 1] = temp;
                }
            }
        }
    }
    void sort_players(){
        int val_compare;
        int initial_val = leaderboard_info[0].time_val;
        int biggest_val;
        for (int i = 0; i < leaderboard_info.size(); ++i){
            val_compare = leaderboard_info[i].time_val;
            if (initial_val < val_compare){
                initial_val = val_compare;
            }
        }

        biggest_val = initial_val;

        for (int i = 0; i < leaderboard_info.size(); ++i){
            if (leaderboard_info[i].time_val == biggest_val){

                leaderboard_info.erase(leaderboard_info.begin() + i);
                break;
            }
        }

    }

    //IMAGE DATA ------------------------------------------------------------------------------------------------------
    void read_imagedata(vector<string>& filepaths) {
        string current_file;
        for (int i = 0; i < filepaths.size(); ++i){
            current_file = filepaths[i];
            sf::Texture* texture = new sf::Texture;
            if (!texture->loadFromFile(current_file)) {
                cerr << "Failed to load texture: " << current_file << endl;
                return;
            }

            unsigned int last_slash = current_file.find_last_of("/");
            unsigned int last_dot = current_file.find_last_of(".");
            current_file = current_file.substr(last_slash + 1,last_dot - last_slash - 1);
            //map key with simple file names
            texturemap[current_file] = texture;
        }

    }

    map<string, sf::Texture*>& get_textures() {
        return texturemap;
    }

};
#endif //PROJECT_3_DATA_H