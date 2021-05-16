#include "../Headers/Entity.h"

Entity::Entity(
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim, 
	Entity_type type_) :
	anim_map(file, anims, first_anim),
	name("Entity"), type(type_)
{
	dir = true; life = true; dead = false;
	feel = Entity_feeling::no_hit;
	state = Entity_state::stay;

	deadtime = 0;
}

///////////////////////Coca/////////////////////////////////

Coca::Coca(const float X, const float Y,
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim) :
	Entity(anims, file, first_anim, Entity_type::Coca)
{
	health = 100;
    w=COCA_W; h = COCA_H;
	x = X; y = Y;
	dx = 0; dy = 0;
	name = "Coca";
}
void Coca::Walk(const float X, const float Y) {
	float dis_x = X - x;
    float dis_y = Y - y;
    float dis = std::sqrt(int(dis_x * dis_x + dis_y * dis_y));
	static size_t r = 0;

	if (std::abs(dis_x) > 64 || dis > 100) {
	    r += 1;
	    if (r > 5000) {

	        r -= 5000;

	        int k = std::abs(rand() % 3);
	        int k_j = std::abs(rand() % 2);

            switch (k) {
                case 0 : {dx = 0.03; dir = true; state = Entity_state::go; break;}
                case 1 : {dx = 0; state = Entity_state::stay; break;}
                case 2 : {dx = -0.03; dir = false; state = Entity_state::go; break;}
            }

            if (k_j) dy = -0.20;
	    }
		//state = Entity_state::stay;
		//dx = 0;
	}
	else {
		state = Entity_state::go;
		if (dis_x >= 0) {
			dir = true;
			dx = 0.03;
		}
		else {
			dx = -0.03;
			dir = false;
		}
	}
}
void Coca::update(const float X, const float Y,const float& time, const std::vector<Object>& obj) {
	if (dead) {
		deadtime += time / 800000;
		if (deadtime >= 3)
			life = false;
		else {
			anim_map.tick(time);
		}
	}
	else {
		Walk(X, Y);
		if (state == Entity_state::stay)
			anim_map.setAnimation("stay");
		if (state == Entity_state::go)
			anim_map.setAnimation("go");
		if (state == Entity_state::jump)
			anim_map.setAnimation("jump");

		anim_map.Direction(dir);

		x += dx * time / 800;
		Colision('x', obj);

		dy += time * 0.00000029;
		y += dy * time / 800;
		Colision('y', obj);

		if (health <= 0) {
			dead = true;
			anim_map.setAnimation("dead");
			dx = 0; dy = 0;
		}

		anim_map.tick(time);
	}
}
void Coca::Colision(const char d, const std::vector<Object>& obj) {
	for (int i = 0; i < obj.size(); i++)
		if (GetRect().intersects(obj[i].rect))
		{
			if (obj[i].type == Object_type::solid)
			{
				if (dy > 0 && d == 'y') { y = obj[i].rect.top - h;  dy = 0;   state = Entity_state::stay; }
				else if (dy < 0 && d == 'y') { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				else if (dx > 0 && d == 'x') { x = obj[i].rect.left - w; }
				else if (dx < 0 && d == 'x') { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}
///////////////////////////Coca_end//////////////////////////////

////////////////////////Ghost/////////////////////////////////////

Ghost::Ghost(const float X, const float Y,
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim) :
	Entity(anims, file, first_anim, Entity_type::Ghost)
{
	health = 100;
	w = GHOST_W; h = GHOST_H;
	x = X; y = Y;
	dx = 0; dy = 0;
	name = "Ghost";
	state = Entity_state::go;
}

void Ghost::Walk(const float X, const float Y) {

    static size_t rand_go_time = 0;

	float dis_x = X - x;
	float dis_y = Y - y;
	float dis = std::sqrt(int(dis_x * dis_x + dis_y * dis_y));
	if (std::abs(dis) > 75) {
		rand_go_time += 1;
		if (rand_go_time >= 2500) {
		    rand_go_time -= 2500;

            int k1 = std::abs(rand() % 2);
            int k2 = std::abs(rand() % 2);
		    int dir_x = k1 ? 1 : -1;
		    int dir_y = k2 ? 1 : -1;

		    dir = !(dir_x - 1);
            dx = 0.03 * dir_x;
            dy = 0.02 * dir_y;
		}
	}
	else {
		
		if (dis_x >= 0 && dis_y >= 0) {
			dir = true;
			dx = 0.04;
			dy = 0.03;
		}
		else if (dis_x > 0 && dis_y < 0) {
            dir = true;
            dx = 0.04;
            dy = -0.03;
		}
        else if (dis_x < 0 && dis_y > 0) {
            dir = false;
            dx = -0.04;
            dy = 0.03;
        }
        else if (dis_x < 0 && dis_y < 0) {
            dir = false;
            dx = -0.04;
            dy = -0.03;
        }
	}
}

void Ghost::update(const float X, const float Y, const float& time, const std::vector<Object>& obj) {
	if (dead) {
		deadtime += time / 800000;
		if (deadtime >= 3)
			life = false;
		else {
			anim_map.tick(time);
		}
	}
	else {
		Walk(X, Y);

		anim_map.setAnimation("go");


		anim_map.Direction(dir);

		x += dx * time / 800;
		Colision('x', obj);

		y += dy * time / 800;
		Colision('y', obj);

		if (health <= 0) {
			dead = true;
			anim_map.setAnimation("dead");
			dx = 0; dy = 0;
		}

		anim_map.tick(time);
	}
}

void Ghost::Colision(const char d, const std::vector<Object>& obj) {

    for (int i = 0; i < obj.size(); i++)
        if (GetRect().intersects(obj[i].rect))
        {
            if (obj[i].type == Object_type::solid)
            {
                if (dy > 0 && d == 'y') { y = obj[i].rect.top - h;  dy *= -1;   state = Entity_state::stay; }
                else if (dy < 0 && d == 'y') { y = obj[i].rect.top + obj[i].rect.height;   dy *= -1; }
                else if (dx > 0 && d == 'x') { x = obj[i].rect.left - w; dx *= -1; }
                else if (dx < 0 && d == 'x') { x = obj[i].rect.left + obj[i].rect.width; dx *= -1; }
            }
        }

}
///////////////////////Ghost_end///////////////////////////////

//////////////////////Bullet///////////////////////////////////

Bullet::Bullet(
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim, const Entity_type _type) :
	Entity(anims, file, first_anim, _type)
{
	life = true;
	name = "Bullet";
	health = 10;
}

 
void Bullet::Colision(const char d, const std::vector<Object>& obj) {
	for (int i = 0; i < obj.size(); i++)
		if (GetRect().intersects(obj[i].rect))
		{
			if (obj[i].type == Object_type::solid)
			{
				life = false;
			}
		}
}
//..................HeroBullet.......................//

HeroBullet::HeroBullet(const float X, const float Y,
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim, bool dir) :
	Bullet(anims,file,first_anim, Entity_type::HeroBullet)
{
	x = X; y = Y; dx = (0.4 * (dir - 0.5)); dy = 0;
	w = HERO_BUL_W; h=HERO_BUL_H;
	name = "HeroBullet";
	anim_map.setAnimation("go");
}

void HeroBullet::update(const float X, const float Y, const float& time, const std::vector<Object>& obj) {
	Walk(X, Y);
	x += dx * time / 800;
	Colision('x', obj);

	anim_map.tick(time);
}

void HeroBullet::Walk(const float X, const float Y) {
}

//...............HeroBullet_end................//

//////////////////Bullet_end/////////////////////////////////////

