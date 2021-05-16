#pragma once
#include "info.h"

class Animation {
public:

	Animation() {};
	Animation(const p_vec_Rect& Frames, sf::Texture &texture);

	void ChangeFrame(const float &time);

	void SetPosition(const float& x, const float& y) { sprite.setPosition(x, y); };
	const sf::Sprite& GetSprite() const { return sprite; };
	void playing(const bool state) { play = state; };
	void Change_dir(const bool dir) { direction = dir; };
private:
	std::vector <sf::IntRect> frames_right;
	std::vector <sf::IntRect> frames_left;
	sf::Sprite sprite;

	size_t frames_size;
	float speed, current_frame;
	bool play, direction; // right =true , left = false
};

class AnimationMap {
public:
	AnimationMap(const std::string& file, 
		const std::map <std::string, p_vec_Rect>& anims,
		const std::string& begin_anim);
	void draw(sf::RenderWindow& window, const float& x, const float& y);

	void setAnimation(const std::string& name) {
		Playing(false);
		current_Animation = name;
		Playing(true);
	};
    void Playing(const bool state) {Animations[current_Animation].playing(state); };
	void Direction(const bool dir) { Animations[current_Animation].Change_dir(dir); };
	void tick(const float time) { Animations[current_Animation].ChangeFrame(time); };
	
private:
	std::string current_Animation;
	sf::Image image;
	sf::Texture Anim_Texture;
	std::map <std::string, Animation> Animations;
};

