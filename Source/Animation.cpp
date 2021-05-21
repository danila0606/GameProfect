#include "../Headers/Animation.h"


Animation::Animation(const p_vec_Rect& Frames, sf::Texture &texture) :
        frames_left_(Frames.first),
        frames_right_(Frames.second)
{
    play_ = false; direction_ = true;
    speed_ = ANIMATION_SPEED;
    current_frame_ = 0;
    frames_size_ = frames_right_.size();
	sprite_.setTexture(texture);
}

void Animation::ChangeFrame(const float& time) {
	if (!play_)
		return;

    current_frame_ += time * speed_ / 800;
	if (current_frame_ >= frames_size_)
        current_frame_ -= frames_size_ * (int(current_frame_) / frames_size_);

	if (!direction_) {
		sprite_.setTextureRect(frames_left_[int(current_frame_)]);
	} 
	else {
		sprite_.setTextureRect(frames_right_[int(current_frame_)]);
	}

}


AnimationMap::AnimationMap(const std::string& file, 
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& begin_anim):
        current_animation_(begin_anim)
{
	image_.loadFromFile(file);
	image_.createMaskFromColor(sf::Color(28, 27, 27));
	anim_texture_.loadFromImage(image_);
	for (const auto& i : anims) {
        animations_[i.first] = Animation(i.second , anim_texture_);
	}
};

void AnimationMap::Draw(sf::RenderWindow& window, const float& x, const float& y) {
	animations_[current_animation_].SetPosition(x, y);
	window.draw(animations_[current_animation_].GetSprite());
}

