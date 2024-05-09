#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

class Button {
    sf::Sprite sprite;

public:
    bool isEnabled = true;
    Button (sf::Texture* texture_name, float position_x, float position_y){
       sprite.setTexture(*texture_name);
       sprite.setPosition(sf::Vector2f(position_x,position_y));

    }

    sf::Sprite get_button(){
        return sprite;
    }

    void set_sprite(sf::Texture* texture_name){
        sprite.setTexture(*texture_name);
    }


};

#ifndef PROJECT_3_BUTTONS_H
#define PROJECT_3_BUTTONS_H

#endif //PROJECT_3_BUTTONS_H
