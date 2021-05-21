#pragma once

#include "Animation.h"
#include <SFML/Audio.hpp>

class Entity;

#define PW 16
#define PH 16

#define P_WIDTH 16
#define P_HEIGHT 16

#define LIVES 6

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

	void KeyPress(const std::string& name) { keys_[name] = true;}
	void KeyReset() {
		for (auto& i : keys_)
			i.second = false;
	}

	void CheckKey();
	void Update(const float& time, const std::vector<Object>& obj, const std::vector <Entity*>& ent);
	void Collide(const char d, const std::vector<Object> &obj, const std::vector <Entity*>& ent);
	void Draw(sf::RenderWindow &window) {
        anim_map_.Draw(window, x_, y_);
	}
	sf::FloatRect GetRect() { return sf::FloatRect(x_ , y_  , w_ , h_ ); };
	float GetX() const { return x_; };
	float GetY() const { return y_; };
	bool GetDir() const { return dir_; };
    size_t GetLives() const {return health_;};

private:
	std::map <std::string, bool> keys_;
	float x_, y_, dx_, dy_;
	float ddx_ = 0, ddy_ = 0;
	float w_, h_;
	int health_;

	Player_state state_;
	Player_feeling feel_;
	
	AnimationMap anim_map_;
	bool dir_; //right - true, left - false
	bool shoot = false;

	float hit_time = 0;
	bool hit = false;

	float tp_time = 0;

    sf::SoundBuffer jump_buf;
    sf::Sound jump_sound;

    sf::SoundBuffer damage_buf;
    sf::Sound damage_sound;
};