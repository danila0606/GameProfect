#include "../Headers/Animation.h"


Animation::Animation(const p_vec_Rect& Frames, sf::Texture &texture) :
	frames_left(Frames.first),
	frames_right(Frames.second) 
{
	play = false; direction = true;
	speed = ANIMATION_SPEED;
	current_frame = 0;
	frames_size = frames_right.size();
	sprite.setTexture(texture);
}

void Animation::ChangeFrame(const float& time) {
	if (!play)
		return;
	
	current_frame += time * speed / 800;
	if (current_frame >= frames_size) 
		current_frame -= frames_size * (int(current_frame)/frames_size);

	if (!direction) {
		sprite.setTextureRect(frames_left[int(current_frame)]);
	} 
	else {
		sprite.setTextureRect(frames_right[int(current_frame)]);
	}

}


AnimationMap::AnimationMap(const std::string& file, 
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& begin_anim):
	current_Animation(begin_anim)
{
	image.loadFromFile(file);
	image.createMaskFromColor(sf::Color(28,27,27));
	Anim_Texture.loadFromImage(image);                         
	for (const auto& i : anims) {
		Animations[i.first] = Animation(i.second , Anim_Texture);
	}
};

void AnimationMap::draw(sf::RenderWindow& window, const float& x, const float& y) {
	Animations[current_Animation].SetPosition(x, y);
	window.draw(Animations[current_Animation].GetSprite());
}

