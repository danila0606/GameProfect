#include "../Headers/Game.h"


Game::Game(const std::string& backgrnd, const std::string& mapName):
	AllObjFrames(FramesLoader()), menu("Images//Background.png")
{

	//BackGround_t.loadFromFile(backgrnd);
	//BackGround_s.setTexture(BackGround_t);

	shoot_buf.loadFromFile("Images//shoot.ogg");
	
	lvl.LoadFromFile(mapName);
			
}
std::map <const std::string, std::map <std::string, p_vec_Rect>>
Game::FramesLoader() {
	std::map <const std::string, std::map <std::string, p_vec_Rect>> allObjFrames;
	///////////player//////////
	std::map <std::string, p_vec_Rect> player_anims;

	std::vector<sf::IntRect> Stay_Frames_r = { sf::IntRect(0,1*PH,PW,PH),																								
											   sf::IntRect(0,1*PH,PW,PH),
											   sf::IntRect(PW,1*PH,PW,PH) };
	std::vector<sf::IntRect> Stay_Frames_l = { sf::IntRect(0 + PW,1*PH,-PW,PH),
											   sf::IntRect(0 + PW,1*PH,-PW,PH),
											   sf::IntRect(PW + PW,1*PH,-PW,PH) };
	p_vec_Rect Stay_Frames_pair = { Stay_Frames_l, Stay_Frames_r };
	player_anims["stay"] = Stay_Frames_pair;

	std::vector<sf::IntRect> Go_Frames_r = { sf::IntRect(0,0,PW,PH),
											 sf::IntRect(0 + PW,0,PW,PH),
											 sf::IntRect(0 + 2* PW,0,PW,PH),
		                                     sf::IntRect(0 + 3 * PW,0,PW,PH) };																					
	std::vector<sf::IntRect> Go_Frames_l = { sf::IntRect(0 + PW,0,-PW,PH),
											 sf::IntRect(0 + 2*PW,0,-PW,PH),
											 sf::IntRect(0 + 3*PW,0,-PW,PH),
											 sf::IntRect(0 + 4*PW,0,-PW,PH) };
	p_vec_Rect Go_Frames_pair = { Go_Frames_l, Go_Frames_r };
	player_anims["go"] = Go_Frames_pair;

	std::vector<sf::IntRect> Jump_Frames_r = { sf::IntRect(PW,3 * PH,PW,PH) };
	std::vector<sf::IntRect> Jump_Frames_l = { sf::IntRect(PW + PW,3 * PH,-PW,PH)};
	p_vec_Rect Jump_Frames_pair = { Jump_Frames_l, Jump_Frames_r };
	player_anims["jump"] = Jump_Frames_pair;

    std::vector<sf::IntRect> Hit_Frames_r = { sf::IntRect(0,4 * PH,PW,PH) };
    std::vector<sf::IntRect> Hit_Frames_l = { sf::IntRect(0 + PW,4 * PH,-PW,PH)};
    p_vec_Rect Hit_Frames_pair = { Hit_Frames_l, Hit_Frames_r };
    player_anims["hit"] = Hit_Frames_pair;

	allObjFrames["player"] = player_anims;
	////////////////player_end//////////////

	//////////////Coca/////////////////////
	std::map <std::string, p_vec_Rect> Coca_anims;

	std::vector<sf::IntRect> Coca_Stay_Frames_l = { sf::IntRect(0,2 * PH,PW,PH),
											   sf::IntRect(0,2 * PH,PW,PH),
											   sf::IntRect(PW,2 * PH,PW,PH) };
	std::vector<sf::IntRect> Coca_Stay_Frames_r = { sf::IntRect(0 + PW,2 * PH,-PW,PH),
											   sf::IntRect(0 + PW,2 * PH,-PW,PH),
											   sf::IntRect(PW + PW,2 * PH,-PW,PH) };
	p_vec_Rect Coca_Stay_Frames_pair = { Coca_Stay_Frames_l, Coca_Stay_Frames_r };
	Coca_anims["stay"] = Coca_Stay_Frames_pair;

	std::vector<sf::IntRect> Coca_Go_Frames_l = { sf::IntRect(3 * PW,2 * PH,PW,PH),
											 sf::IntRect(3 * PW + PW,2 * PH,PW,PH),
											 sf::IntRect(3 * PW + 2 * PW,2 * PH,PW,PH)};
	std::vector<sf::IntRect> Coca_Go_Frames_r = { sf::IntRect(3 * PW + PW,2 * PH,-PW,PH),
											 sf::IntRect(3 * PW + 2 * PW,2 * PH,-PW,PH),
											 sf::IntRect(3 * PW + 3 * PW,2 * PH,-PW,PH) };
	p_vec_Rect Coca_Go_Frames_pair = { Coca_Go_Frames_l, Coca_Go_Frames_r };
	Coca_anims["go"] = Coca_Go_Frames_pair;

	std::vector<sf::IntRect> Coca_Dead_Frames_l = { sf::IntRect(194,33,14,16),
											 sf::IntRect(210 ,33,14,16)};																						
	std::vector<sf::IntRect> Coca_Dead_Frames_r = { sf::IntRect(194 + 14,33,-14,16),																				
											 sf::IntRect(210 + 14,33,-14,16)};
	p_vec_Rect Coca_Dead_Frames_pair = { Coca_Dead_Frames_l, Coca_Dead_Frames_r };
	Coca_anims["dead"] = Coca_Dead_Frames_pair;

	allObjFrames["Coca"] = Coca_anims;
	//////////////Coca_end/////////////////////

	/////////////Ghost/////////////////////////
	std::map <std::string, p_vec_Rect> Ghost_anims;

	std::vector<sf::IntRect> Ghost_Go_Frames_l = { sf::IntRect(53,51,7,13)
												  /* sf::IntRect(70,51,7,13),
												   sf::IntRect(86,49,7,13),
												   sf::IntRect(102,50,7,13) */};

	std::vector<sf::IntRect> Ghost_Go_Frames_r = { sf::IntRect(53 + 7,51,-7,13)
												   /*sf::IntRect(70 + 7,51,-7,13),
												   sf::IntRect(86 + 7,49,-7,13),
												   sf::IntRect(102 + 7,50,-7,13)*/ };

	p_vec_Rect Ghost_Go_Frames_pair = { Ghost_Go_Frames_l, Ghost_Go_Frames_r };
	Ghost_anims["go"] = Ghost_Go_Frames_pair;

    std::vector<sf::IntRect> Ghost_Dead_Frames_l = { sf::IntRect(196,51,7,13),
                                                    sf::IntRect(212 ,51,7,13)};
    std::vector<sf::IntRect> Ghost_Dead_Frames_r = { sf::IntRect(196 + 7,51,-7,13),
                                                    sf::IntRect(212 + 7,51,-7,13)};
    p_vec_Rect Ghost_Dead_Frames_pair = { Ghost_Dead_Frames_l, Ghost_Dead_Frames_r };
    Ghost_anims["dead"] = Ghost_Dead_Frames_pair;

	allObjFrames["Ghost"] = Ghost_anims;

	/////////////Ghost_end/////////////////////////

	/////////////HeroBullet//////////////////
	std::map <std::string, p_vec_Rect> HeroBullet_anims;

	std::vector<sf::IntRect> HeroBullet_Go_Frames_l = { sf::IntRect(34,40,3,3) };
											 
	std::vector<sf::IntRect> HeroBullet_Go_Frames_r = { sf::IntRect(34 + 3,40,-3,3) };
											
	p_vec_Rect HeroBullet_Go_Frames_pair = { HeroBullet_Go_Frames_l, HeroBullet_Go_Frames_r };
	HeroBullet_anims["go"] = HeroBullet_Go_Frames_pair;

	allObjFrames["HeroBullet"] = HeroBullet_anims;

	///////////Herobullet_end/////////////////


	return allObjFrames;

}

void Game::Colision(Player& player, std::vector<Entity*>& entities, std::vector<Bullet*>& bullets) {																							
	for (auto iter = entities.begin(); iter != entities.end();) {
		Entity* ent = *iter;
		sf::FloatRect entRect = ent->GetRect();
		for (auto it = bullets.begin(); it != bullets.end();)
		{
			
			Bullet* bul = *it;
			
			if (bul->GetType() == Entity_type::HeroBullet) {

				if (bul->GetRect().intersects(entRect)) {

					bul->Life(false);
					it = bullets.erase(it);
					delete bul;
					ent->Health(-20);
				}
				else { bul++; it++; };
			}
			else { it++; };

		}
		iter++;
	}
	
}

void Game::Load() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");

    while(true) {
        if (!menu.Start(window))
            return;

        if (!Start(window))
            break;
    }

}

bool Game::Start(sf::RenderWindow& window) {

    //...........Loading Objects..............

	if (AllObjFrames.count("player") == 0)
	    throw std::runtime_error("Player anim not found!");

	const Object* player_obj = lvl.GetObject(Object_type::player);
	Player player(player_obj->rect.left, player_obj->rect.top,																											
		AllObjFrames["player"], "Images//player.png", "stay");

	const std::vector<Object> teleports = lvl.GetObjects(Object_type::tp);

	std::vector<Entity*> entities;
	std::vector<Bullet*> bullets;

	const std::vector<Object> ob_coca = lvl.GetObjects(Object_type::Coca);
	if (!AllObjFrames.count("Coca"))
	    throw std::runtime_error("Coca anim not found!");


    const std::vector<Object> ob_ghost = lvl.GetObjects(Object_type::Ghost);
    if (!AllObjFrames.count("Ghost"))
        throw std::runtime_error("Ghost anim not found!");

    entities.reserve(ob_coca.size() + ob_ghost.size());
    for (auto & i : ob_coca)
        entities.push_back(new Coca(i.rect.left, i.rect.top, AllObjFrames["Coca"], "Images//enemies.png", "go"));

    for (auto & i : ob_ghost)
		entities.push_back(new Ghost(i.rect.left, i.rect.top, AllObjFrames["Ghost"], "Images//enemies.png", "go"));


    sf::Sound shoot(shoot_buf);
    //...............Loading_end........................

	sf::View view(sf::FloatRect(0, 0, VIEW_X, VIEW_Y));
    sf::View end_view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    sf::View pause_view(sf::FloatRect(0, 0, PAUSE_X, PAUSE_Y));

    sf::Clock clock;

	while (window.isOpen()) {

		sf::Event event{};
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space && bullet_time > BULLET_TIME) {
				    shoot.play();
				    bullet_time -= BULLET_TIME;
					bullets.push_back(new HeroBullet(player.GetX() + P_WIDTH/2, player.GetY() + P_HEIGHT/2,
						AllObjFrames["HeroBullet"], "Images//player.png", "go", player.GetDir()));
				}
			}
		}
		Colision(player, entities, bullets);
		float time = clock.getElapsedTime().asMicroseconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.KeyPress("Right");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.KeyPress("Left");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.KeyPress("Up");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.KeyPress("Down");

		//............Pause...................
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && pause_time <= 0) {
		    pause_time += 1000000;
            //window.setView(pause_view);
            if (!menu.Pause(window, player.GetX(), player.GetY()))
                return false;

            window.setView(view);
		}
        clock.restart();

		if (pause_time > 0)
		    pause_time -= time;


		//...................................

		spawn_time += time;
		if (bullet_time < BULLET_TIME * BULLET_NUM)
		    bullet_time += time;

		if (spawn_time >= SPAWN_TIME) {
		    spawn_time -= SPAWN_TIME;
            Spawn(teleports, entities);
		}

		player.update(time, lvl.GetAllObjects(), entities);
		for (auto it = entities.begin(); it != entities.end();) {

			Entity* en = *it;
			en->update(player.GetX(), player.GetY(), time, lvl.GetAllObjects());
			if (!en->GetLife()) { it = entities.erase(it); delete en; killes += 1;}
			else 
			    it++;
		}
		for (auto it = bullets.begin(); it != bullets.end();) {

			Bullet* en = *it;
			en->update(player.GetX(), player.GetY(), time, lvl.GetAllObjects());
			if (!en->GetLife()) {
				it = bullets.erase(it); 
				delete en; 
			}
			else
				it++;
		}

		window.clear();

		view.setCenter(player.GetX(), player.GetY());
		window.setView(view);

		lvl.Draw(window);
		player.draw(window);
		for (auto en : entities)
		    en->draw(window);

		for (auto en : bullets)
		    en->draw(window);

		menu.DrawLives(window, player.GetLives(), player.GetX() - VIEW_X/2, player.GetY() - VIEW_Y/2);

		if (player.GetLives() <= 0) {
		    window.setView(end_view);
		    menu.Died(window, player.GetX(), player.GetY(), killes);
		    return true;
		}

		window.display();
	}
}

void Game::Spawn(const std::vector<Object>& tps, std::vector<Entity*>& entities) {

    const size_t num = ENEMY_NUM_PER_SPAWN / 2;

    size_t r = 0;
    const size_t tps_num = tps.size();
    for (size_t i = 0; i < num; ++i) {

        r = rand() % tps_num;
        entities.push_back(new Coca(tps[r].rect.left, tps[r].rect.top, AllObjFrames["Coca"], "Images//enemies.png", "go"));

        r = rand() % tps_num;
        entities.push_back(new Ghost(tps[r].rect.left, tps[r].rect.top, AllObjFrames["Ghost"], "Images//enemies.png", "go"));

    }

}
