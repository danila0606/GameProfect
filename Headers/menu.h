#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cassert>
#include <iostream>

#define LIVES_NUM 10

#define DIED_X 566
#define DIED_Y 126

#define PAUSE_X 256
#define PAUSE_Y 256

enum class Choosed_Button {
    Start,
    Options,
    Exit,
    Nop
};



class Menu final {

public:

    Menu(const std::string& backgrnd);


    bool Start(sf::RenderWindow& window);
    bool Pause(sf::RenderWindow& window, float x, float y);
    void Died (sf::RenderWindow& window, float x, float y, size_t kills);

    void DrawLives(sf::RenderWindow& window, size_t lives, float x, float y);

private:

    sf::Texture BackGround_t;
    sf::Sprite BackGround_s;

    sf::Texture Died_t;
    sf::Sprite Died_s;

    sf::Texture Buttons_t;
    sf::Sprite Start_button_s;
    sf::Sprite Start_button_s_pressed;
    sf::IntRect Start_button_rect;

    sf::Sprite Options_button_s;
    sf::Sprite Options_button_s_pressed;
    sf::IntRect Options_button_rect;

    sf::Sprite Exit_button_s;
    sf::Sprite Exit_button_s_pressed;
    sf::IntRect Exit_button_rect;

    sf::Texture Heart_t;

    sf::Texture Pause_t;
    sf::Sprite Pause_s;

};