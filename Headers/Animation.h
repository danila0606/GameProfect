#pragma once
#include "info.h"

class Animation {
public:

	Animation() {};
	Animation(const p_vec_Rect& Frames, sf::Texture &texture);

	void ChangeFrame(const float &time);

	void SetPosition(const float& x, const float& y) { sprite_.setPosition(x, y); };
	const sf::Sprite& GetSprite() const { return sprite_; };
	void Playing(const bool state) { play_ = state; };
	void ChangeDir(const bool dir) { direction_ = dir; };
private:
	std::vector <sf::IntRect> frames_right_;
	std::vector <sf::IntRect> frames_left_;
	sf::Sprite sprite_;

	size_t frames_size_;
	float speed_, current_frame_;
	bool play_, direction_; // right =true , left = false
};

class AnimationMap {
public:
	AnimationMap(const std::string& file, 
		const std::map <std::string, p_vec_Rect>& anims,
		const std::string& begin_anim);
	void Draw(sf::RenderWindow& window, const float& x, const float& y);

	void SetAnimation(const std::string& name) {
		Playing(false);
        current_animation_ = name;
		Playing(true);
	};
    void Playing(const bool state) { animations_[current_animation_].Playing(state); };
	void ChangeDirection(const bool dir) { animations_[current_animation_].ChangeDir(dir); };
	void Tick(const float time) { animations_[current_animation_].ChangeFrame(time); };
	
private:
	std::string current_animation_;
	sf::Image image_;
	sf::Texture anim_texture_;
	std::map <std::string, Animation> animations_;
};

