#pragma once
#include "Animation.h"
#include <cmath>

////////////const list////////////

#define COCA_W 16
#define COCA_H 16

#define GHOST_W 7
#define GHOST_H 13

#define HERO_BUL_W 3
#define HERO_BUL_H 3













////////////////////////////////////

enum class Entity_state {
	stay,
	go, 
	jump
};
enum class Entity_feeling {
	no_hit,
	hit,
	dead
};

enum class Entity_type {
	Coca,
	HeroBullet,
	Ghost
};

class Entity {

public: 
	Entity(
		const std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim, 
		Entity_type type);

	virtual void Walk(const float X, const float Y) = 0;
	virtual void Update(const float X, const float Y, const float& time, const std::vector<Object>& obj) = 0;
	virtual void Collide(const char d, const std::vector<Object>& obj) = 0;
	void draw(sf::RenderWindow& window) {
        anim_map_.Draw(window, x_, y_);
	}
	sf::FloatRect GetRect() { return sf::FloatRect(x_, y_, w_, h_); };
	void Health(int h) { health_ += h; };

	std::string GetName() const { return name_; };
	Entity_type GetType() const { return type_; };
	bool GetLife() const { return life_; };
	void Life(const bool l) { life_ = l; };
	bool GetDead() const { return dead_; };
	void Dead(const bool l) { dead_ = l; };

    float GetX() const {return x_;};
    float GetY() const {return y_;};
protected:
	std::string name_;

	Entity_state state_;
	Entity_feeling feel_;
	Entity_type type_;

	AnimationMap anim_map_;
	bool dir_; //right - true, left - false
	//bool shoot;
	bool life_, dead_;
	
	float deadtime_;

	float x_{}, y_{}, dx_{}, dy_{};
	float w_{}, h_{};
	int health_{};

public:
    virtual ~Entity() = default;
};

class Coca final: public Entity {
public:
	Coca(const float X, const float Y, const
		std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim);

	void Update(const float X, const float Y, const float& time, const std::vector<Object>& obj);
	void Collide(const char d, const std::vector<Object>& obj);
	void Walk(const float X, const float Y);

    ~Coca() = default;
};

class Ghost final: public Entity {
public:
	Ghost(const float X, const float Y, const
		std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim);

	sf::FloatRect GetRect() const { return sf::FloatRect(x_, y_, w_, h_); };

	void Update(const float X, const float Y, const float& time, const std::vector<Object>& obj);
	void Collide(const char d, const std::vector<Object>& obj);
	void Walk(const float X, const float Y);

	~Ghost() = default;
};

class Bullet : public Entity {
public:
	Bullet(
		const std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim, const Entity_type _type);

	void Collide(const char d, const std::vector<Object>& obj);

	virtual void Update(const float X, const float Y, const float& time, const std::vector<Object>& obj) = 0;
	virtual void Walk(const float X, const float Y) = 0;
};

class HeroBullet final : public Bullet {
public:
	HeroBullet(const float X, const float Y,
		const std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim, bool dir);

	void Update(const float X, const float Y, const float& time, const std::vector<Object>& obj);
	void Walk(const float X, const float Y);
};