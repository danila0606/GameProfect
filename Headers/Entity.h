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
		Entity_type type_);

	virtual void Walk(const float X, const float Y) = 0;
	virtual void update(const float X, const float Y,const float& time, const std::vector<Object>& obj) = 0;
	virtual void Colision(const char d, const std::vector<Object>& obj) = 0;
	void draw(sf::RenderWindow& window) {
		anim_map.draw(window, x, y);
	}
	sf::FloatRect GetRect() { return sf::FloatRect(x, y, w, h); };
	void Health(int h) { health += h; };

	std::string GetName() const { return name; };
	Entity_type GetType() const { return type; };
	bool GetLife() const { return life; };
	void Life(const bool l) { life = l; };
	bool GetDead() const { return dead; };
	void Dead(const bool l) { dead = l; };

    float GetX() const {return x;};
    float GetY() const {return y;};
protected:
	std::string name;

	Entity_state state;
	Entity_feeling feel;
	Entity_type type;

	AnimationMap anim_map;
	bool dir; //right - true, left - false
	//bool shoot;
	bool life, dead;
	
	float deadtime;

	float x{}, y{}, dx{}, dy{};
	float w{}, h{};
	int health{};

public:
    virtual ~Entity() = default;
};

class Coca final: public Entity {
public:
	Coca(const float X, const float Y, const
		std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim);

	void update(const float X, const float Y,const float& time, const std::vector<Object>& obj);
	void Colision(const char d, const std::vector<Object>& obj);
	void Walk(const float X, const float Y);

    ~Coca() = default;
};

class Ghost final: public Entity {
public:
	Ghost(const float X, const float Y, const
		std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim);

	sf::FloatRect GetRect() const { return sf::FloatRect(x, y, w, h); };

	void update(const float X, const float Y, const float& time, const std::vector<Object>& obj);
	void Colision(const char d, const std::vector<Object>& obj);
	void Walk(const float X, const float Y);

	~Ghost() = default;
};

class Bullet : public Entity {
public:
	Bullet(
		const std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim, const Entity_type _type);

	void Colision(const char d, const std::vector<Object>& obj);

	virtual void update(const float X, const float Y, const float& time, const std::vector<Object>& obj) = 0;
	virtual void Walk(const float X, const float Y) = 0;
};

class HeroBullet final : public Bullet {
public:
	HeroBullet(const float X, const float Y,
		const std::map <std::string, p_vec_Rect>& anims,
		const std::string& file, const std::string& first_anim, bool dir);

	void update(const float X, const float Y, const float& time, const std::vector<Object>& obj);
	void Walk(const float X, const float Y);
};