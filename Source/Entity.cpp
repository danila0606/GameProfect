#include "../Headers/Entity.h"

Entity::Entity(
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim, 
	Entity_type type) :
        anim_map_(file, anims, first_anim),
        name_("Entity"), type_(type)
{
    dir_ = true; life_ = true; dead_ = false;
    feel_ = Entity_feeling::no_hit;
    state_ = Entity_state::stay;

    deadtime_ = 0;
}

///////////////////////Coca/////////////////////////////////

Coca::Coca(const float X, const float Y,
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim) :
	Entity(anims, file, first_anim, Entity_type::Coca)
{
    health_ = 40;
    w_=COCA_W; h_ = COCA_H;
    x_ = X; y_ = Y;
    dx_ = 0; dy_ = 0;
    name_ = "Coca";
}
void Coca::Walk(const float X, const float Y) {
	float dis_x = X - x_;
    float dis_y = Y - y_;
    float dis = std::sqrt(int(dis_x * dis_x + dis_y * dis_y));
	static size_t r = 0;

	if (std::abs(dis_x) > 64 || dis > 100) {
	    r += 1;
	    if (r > 5000) {

	        r -= 5000;

	        int k = std::abs(rand() % 3);
	        int k_j = std::abs(rand() % 2);

            switch (k) {
                case 0 : { dx_ = 0.03; dir_ = true; state_ = Entity_state::go; break;}
                case 1 : { dx_ = 0; state_ = Entity_state::stay; break;}
                case 2 : { dx_ = -0.03; dir_ = false; state_ = Entity_state::go; break;}
            }

            if (k_j) dy_ = -0.20;
	    }
		//state_ = Entity_state::stay;
		//dx_ = 0;
	}
	else {
        state_ = Entity_state::go;
		if (dis_x >= 0) {
            dir_ = true;
            dx_ = 0.03;
		}
		else {
            dx_ = -0.03;
            dir_ = false;
		}
	}
}
void Coca::Update(const float X, const float Y, const float& time, const std::vector<Object>& obj) {
	if (dead_) {
        deadtime_ += time / 800000;
		if (deadtime_ >= 3)
            life_ = false;
		else {
            anim_map_.Tick(time);
		}
	}
	else {
		Walk(X, Y);
		if (state_ == Entity_state::stay)
            anim_map_.SetAnimation("stay");
		if (state_ == Entity_state::go)
            anim_map_.SetAnimation("go");
		if (state_ == Entity_state::jump)
            anim_map_.SetAnimation("jump");

        anim_map_.ChangeDirection(dir_);

        x_ += dx_ * time / 800;
        Collide('x', obj);

        dy_ += time * 0.00000029;
        y_ += dy_ * time / 800;
        Collide('y', obj);

		if (health_ <= 0) {
            dead_ = true;
            anim_map_.SetAnimation("dead_");
            dx_ = 0; dy_ = 0;
		}

        anim_map_.Tick(time);
	}
}
void Coca::Collide(const char d, const std::vector<Object>& obj) {
	for (int i = 0; i < obj.size(); i++)
		if (GetRect().intersects(obj[i].rect))
		{
			if (obj[i].type == Object_type::solid)
			{
				if (dy_ > 0 && d == 'y') { y_ = obj[i].rect.top - h_; dy_ = 0; state_ = Entity_state::stay; }
				else if (dy_ < 0 && d == 'y') { y_ = obj[i].rect.top + obj[i].rect.height; dy_ = 0; }
				else if (dx_ > 0 && d == 'x') { x_ = obj[i].rect.left - w_; }
				else if (dx_ < 0 && d == 'x') { x_ = obj[i].rect.left + obj[i].rect.width; }
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
    health_ = 20;
    w_ = GHOST_W; h_ = GHOST_H;
    x_ = X; y_ = Y;
    dx_ = 0; dy_ = 0;
    name_ = "Ghost";
    state_ = Entity_state::go;
}

void Ghost::Walk(const float X, const float Y) {

    static size_t rand_go_time = 0;

	float dis_x = X - x_;
	float dis_y = Y - y_;
	float dis = std::sqrt(int(dis_x * dis_x + dis_y * dis_y));
	if (std::abs(dis) > 75) {
		rand_go_time += 1;
		if (rand_go_time >= 2500) {
		    rand_go_time -= 2500;

            int k1 = std::abs(rand() % 2);
            int k2 = std::abs(rand() % 2);
		    int dir_x = k1 ? 1 : -1;
		    int dir_y = k2 ? 1 : -1;

            dir_ = !(dir_x - 1);
            dx_ = 0.03 * dir_x;
            dy_ = 0.02 * dir_y;
		}
	}
	else {
		
		if (dis_x >= 0 && dis_y >= 0) {
            dir_ = true;
            dx_ = 0.04;
            dy_ = 0.03;
		}
		else if (dis_x > 0 && dis_y < 0) {
            dir_ = true;
            dx_ = 0.04;
            dy_ = -0.03;
		}
        else if (dis_x < 0 && dis_y > 0) {
            dir_ = false;
            dx_ = -0.04;
            dy_ = 0.03;
        }
        else if (dis_x < 0 && dis_y < 0) {
            dir_ = false;
            dx_ = -0.04;
            dy_ = -0.03;
        }
	}
}

void Ghost::Update(const float X, const float Y, const float& time, const std::vector<Object>& obj) {
	if (dead_) {
        deadtime_ += time / 800000;
		if (deadtime_ >= 3)
            life_ = false;
		else {
            anim_map_.Tick(time);
		}
	}
	else {
		Walk(X, Y);

        anim_map_.SetAnimation("go");


        anim_map_.ChangeDirection(dir_);

        x_ += dx_ * time / 800;
        Collide('x', obj);

        y_ += dy_ * time / 800;
        Collide('y', obj);

		if (health_ <= 0) {
            dead_ = true;
            anim_map_.SetAnimation("dead_");
            dx_ = 0; dy_ = 0;
		}

        anim_map_.Tick(time);
	}
}

void Ghost::Collide(const char d, const std::vector<Object>& obj) {

    for (int i = 0; i < obj.size(); i++)
        if (GetRect().intersects(obj[i].rect))
        {
            if (obj[i].type == Object_type::solid)
            {
                if (dy_ > 0 && d == 'y') { y_ = obj[i].rect.top - h_; dy_ *= -1; state_ = Entity_state::stay; }
                else if (dy_ < 0 && d == 'y') { y_ = obj[i].rect.top + obj[i].rect.height; dy_ *= -1; }
                else if (dx_ > 0 && d == 'x') { x_ = obj[i].rect.left - w_; dx_ *= -1; }
                else if (dx_ < 0 && d == 'x') { x_ = obj[i].rect.left + obj[i].rect.width; dx_ *= -1; }
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
    life_ = true;
    name_ = "Bullet";
    health_ = 10;
}

 
void Bullet::Collide(const char d, const std::vector<Object>& obj) {
	for (int i = 0; i < obj.size(); i++)
		if (GetRect().intersects(obj[i].rect))
		{
			if (obj[i].type == Object_type::solid)
			{
                life_ = false;
			}
		}
}
//..................HeroBullet.......................//

HeroBullet::HeroBullet(const float X, const float Y,
	const std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim, bool dir) :
	Bullet(anims,file,first_anim, Entity_type::HeroBullet)
{
    x_ = X; y_ = Y; dx_ = (0.4 * (dir - 0.5)); dy_ = 0;
    w_ = HERO_BUL_W; h_=HERO_BUL_H;
    name_ = "HeroBullet";
    anim_map_.SetAnimation("go");
}

void HeroBullet::Update(const float X, const float Y, const float& time, const std::vector<Object>& obj) {
	Walk(X, Y);
    x_ += dx_ * time / 800;
    Collide('x', obj);

    anim_map_.Tick(time);
}

void HeroBullet::Walk(const float X, const float Y) {
}

//...............HeroBullet_end................//

//////////////////Bullet_end/////////////////////////////////////

