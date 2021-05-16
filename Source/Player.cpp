#include "../Headers/PLayer.h"
#include "../Headers/Entity.h"


Player::Player(const float X, const float Y, const
	std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim) :
	anim_map(file, anims, first_anim)
{
	x = X; y = Y;
	dx = 0; dy = 0;
	w = P_WIDTH; h = P_HEIGHT;
	health = LIVES;
	dir = true;
	feel = Player_feeling::no_hit;
	state = Player_state::stay;
	shoot = false;

	Keys["Left" ] = false;
	Keys["Right"] = false;
	Keys["Up"   ] = false;
	Keys["Down" ] = false;
	Keys["Space"] = false;
	Keys["Ctrl" ] = false;

	jump_buf.loadFromFile("Images//jump.ogg");
	jump_sound.setBuffer(jump_buf);

    damage_buf.loadFromFile("Images//damage.ogg");
    damage_sound.setBuffer(damage_buf);

}

void Player::CheckKey() {

    if (hit > 0) {
        dx = 0.01;
        dy = -0.15;
        hit = false;
        return;
    }

    if (hit_time > 0)
        return;

	if (Keys["Right"] && !Keys["Left"]) {

		dir = true;
		dx = 0.1;
		if (state == Player_state::stay)
			state = Player_state::go;

		if (state == Player_state::jump)
			dx = 0.07;

	}
	if (!Keys["Right"] && Keys["Left"]) {
		dir = false;
		dx = -0.1;

		if (state == Player_state::stay)
			state = Player_state::go;

		if (state == Player_state::jump)
			dx = -0.07;
	}
	if (Keys["Right"] && Keys["Left"]) {

		if (state == Player_state::go)
			state = Player_state::stay;

		dx = 0;
	}

	if (!Keys["Right"] && !Keys["Left"]) {

		if (state == Player_state::go)
			state = Player_state::stay;

		dx = 0;
	}

	if (Keys["Up"] && feel == Player_feeling::no_hit) {
			
		if (state == Player_state::stay || state == Player_state::go) {
			state = Player_state::jump;
			dy = -0.15;
		}
	}
	
	if (!Keys["Up"] ) {
	

	}

	if (Keys["Ctrl"]) {
		shoot = true;
	}
	if (!Keys["Ctrl"]) {
		shoot = false;
	}

}

void Player::update(const float& time, const std::vector<Object>& obj, const std::vector <Entity*>& ent) {

	CheckKey();

	if (tp_time > 0)
	    tp_time -= time;

	if (hit_time > 0) {
	    hit_time -= time;
        anim_map.setAnimation("hit");
	}
    else {
        hit_time = 0;
        feel = Player_feeling::no_hit;

        if (state == Player_state::stay)
            anim_map.setAnimation("stay");
        if (state == Player_state::go)
            anim_map.setAnimation("go");
        if (state == Player_state::jump)
            anim_map.setAnimation("jump");

    }

	anim_map.Direction(dir);
			
	x += dx * time / 800;
	Colision('x', obj, ent);

	dy += time * 0.00000029;
	y += dy * time /800;
	Colision('y', obj, ent);

	KeyReset();
	anim_map.tick(time);
}

void Player::Colision(const char d, const std::vector<Object> &obj, const std::vector <Entity*>& ent) {
	
	for (const auto & i : obj)
		if (GetRect().intersects(i.rect)) {

			if (i.type == Object_type::solid)
			{
				if (dy > 0 && d == 'y') { y = i.rect.top - h;  dy = 0;   state = Player_state::stay; }
				else if (dy < 0 && d == 'y') { y = i.rect.top + i.rect.height;   dy = 0; }
				else if (dx > 0 && d == 'x') { x = i.rect.left - w; }
				else if (dx < 0 && d == 'x') { x = i.rect.left + i.rect.width; }
			}
			else if (i.type == Object_type::jumper) {
                dy = -0.3;
                state = Player_state::jump;
                jump_sound.play();
            }
            else if (i.type == Object_type::tp && tp_time <= 0) {
                std::vector<Object> tps;
                auto it = obj.begin();
                while (it != obj.end()) {

                    auto iter = std::find_if(it, obj.end(), [](const Object& ob) { return ob.type == Object_type::tp; });
                    tps.push_back(*it);
                    it = iter + 1;
                }

                int i = rand() % tps.size();

                x = tps[i].rect.left;
                y = tps[i].rect.top;
                tp_time += 1000000;
            }
		}

	for (auto* ent : ent) {

			if (GetRect().intersects(ent->GetRect())) {
                if (ent->GetType() == Entity_type::Coca) {
                    if (feel == Player_feeling::no_hit && !ent->GetDead()) {
                        damage_sound.play();
                        feel = Player_feeling::hit;
                        health -= 1;
                        hit_time = 1500000;
                        hit = true;
                    }

                    if (dy > 0 && d == 'y') { state = Player_state::jump; dy *= -0.5;}
                        ent->Health(-200);
                }
                else if (ent->GetType() == Entity_type::Ghost) {
                    if (feel == Player_feeling::no_hit && !ent->GetDead()) {
                        damage_sound.play();
                        feel = Player_feeling::hit;
                        health -= 1;
                        hit_time = 1500000;

                        if (dy > 0 && d == 'y')
                            state = Player_state::jump; dy *= -0.5;

                        hit = true;
                        ent->Health(-200);
                    }
                }

		}
	}
}