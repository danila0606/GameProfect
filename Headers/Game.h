#pragma once
#include "PLayer.h"
#include "Entity.h"
#include "parser.h"
#include "menu.h"
#include <exception>


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define VIEW_X 400.f
#define VIEW_Y 300.f

#define ENEMY_NUM_PER_SPAWN 4
#define SPAWN_TIME 5000000
#define BULLET_TIME 500000
#define BULLET_NUM 6

class Game final {
public:
	Game(const std::string& backgrnd, const std::string& mapName);

	void Load();
private:

    bool Start(sf::RenderWindow& window);
    static std::map <const std::string, std::map <std::string, p_vec_Rect>> FramesLoader();
    void Collide(Player& player, std::vector<Entity*>& entities, std::vector<Bullet*>& bullets);

    void Spawn(const std::vector<Object>& tps, std::vector<Entity*>& entities);

private:

	Level lvl_;
	Menu menu_;
	std::map <const std::string, std::map <std::string, p_vec_Rect>> AllObjFrames_;

	//sf::Texture BackGround_t;
	//sf::Sprite BackGround_s;

    sf::SoundBuffer shoot_buf;

	float pause_time_ = 0;
	float spawn_time_ = 0;
	float bullet_time_ = 0; //delete, UML
	size_t killes_ = 0;
};