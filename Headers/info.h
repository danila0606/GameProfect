#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <assert.h>

typedef std::pair<std::vector<sf::IntRect>, std::vector<sf::IntRect>> p_vec_Rect;
////////////Object//////////////
enum class Object_type {
    solid,
    player,
    Coca,
    Ghost,
    jumper,
    tp,
    unknown
};



struct Object {
    std::string name;
    Object_type type;
    sf::Rect<float> rect;

    int id;
    sf::Sprite sprite;
};
//////////Animation///////////

#define ANIMATION_SPEED 0.005