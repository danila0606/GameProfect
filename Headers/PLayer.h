#pragma once

#include "Animation.h"
#include <SFML/Audio.hpp>

class Entity;

#define PW 16
#define PH 16

#define P_WIDTH 16
#define P_HEIGHT 16

#define LIVES 1

enum class Player_state {
	stay,
	go,
	jump
};

enum class Player_feeling {
	no_hit, 
	hit,
	dead
};

class Player {
	
public:
	Player(const float X, const float Y, const
		std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim);

	void KeyPress(const std::string& name) { Keys[name] = true;}
	void KeyReset() {
		for (auto& i : Keys)
			i.second = false;
	}

	void CheckKey();
	void update(const float& time, const std::vector<Object>& obj, const std::vector <Entity*>& ent);
	void Colision(const char d, const std::vector<Object> &obj, const std::vector <Entity*>& ent);
	void draw(sf::RenderWindow &window) {
		anim_map.draw(window, x, y);
	}
	sf::FloatRect GetRect() { return sf::FloatRect(x , y  , w , h ); };
	float GetX() const { return x; };
	float GetY() const { return y; };
	bool GetDir() const { return dir; };
    size_t GetLives() const {return health;};

private:
	std::map <std::string, bool> Keys;
	float x, y, dx, dy;
	float ddx = 0, ddy = 0;
	float w, h;
	int health;

	Player_state state;
	Player_feeling feel;
	
	AnimationMap anim_map;
	bool dir; //right - true, left - false
	bool shoot = false;

	float hit_time = 0;
	bool hit = false;

	float tp_time = 0;

    sf::SoundBuffer jump_buf;
    sf::Sound jump_sound;

    sf::SoundBuffer damage_buf;
    sf::Sound damage_sound;
};