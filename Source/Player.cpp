#include "../Headers/PLayer.h"
#include "../Headers/Entity.h"


Player::Player(const float X, const float Y, const
	std::map <std::string, p_vec_Rect>& anims,
	const std::string& file, const std::string& first_anim) :
        anim_map_(file, anims, first_anim)
{
    x_ = X; y_ = Y;
    dx_ = 0; dy_ = 0;
    w_ = P_WIDTH; h_ = P_HEIGHT;
    health_ = LIVES;
    dir_ = true;
    feel_ = Player_feeling::no_hit;
    state_ = Player_state::stay;
	shoot = false;

    keys_["Left" ] = false;
    keys_["Right"] = false;
    keys_["Up"   ] = false;
    keys_["Down" ] = false;
    keys_["Space"] = false;
    keys_["Ctrl" ] = false;

	jump_buf.loadFromFile("Images//jump.ogg");
	jump_sound.setBuffer(jump_buf);

    damage_buf.loadFromFile("Images//damage.ogg");
    damage_sound.setBuffer(damage_buf);

}

void Player::CheckKey() {

    if (hit > 0) {
        dx_ = 0.01;
        dy_ = -0.15;
        hit = false;
        return;
    }

    if (hit_time > 0)
        return;

	if (keys_["Right"] && !keys_["Left"]) {

        dir_ = true;
        dx_ = 0.1;
		if (state_ == Player_state::stay)
            state_ = Player_state::go;

		if (state_ == Player_state::jump)
            dx_ = 0.07;

	}
	if (!keys_["Right"] && keys_["Left"]) {
        dir_ = false;
        dx_ = -0.1;

		if (state_ == Player_state::stay)
            state_ = Player_state::go;

		if (state_ == Player_state::jump)
            dx_ = -0.07;
	}
	if (keys_["Right"] && keys_["Left"]) {

		if (state_ == Player_state::go)
            state_ = Player_state::stay;

        dx_ = 0;
	}

	if (!keys_["Right"] && !keys_["Left"]) {

		if (state_ == Player_state::go)
            state_ = Player_state::stay;

        dx_ = 0;
	}

	if (keys_["Up"] && feel_ == Player_feeling::no_hit) {
			
		if (state_ == Player_state::stay || state_ == Player_state::go) {
            state_ = Player_state::jump;
            dy_ = -0.15;
		}
	}
	
	if (!keys_["Up"] ) {
	

	}

	if (keys_["Ctrl"]) {
		shoot = true;
	}
	if (!keys_["Ctrl"]) {
		shoot = false;
	}

}

void Player::Update(const float& time, const std::vector<Object>& obj, const std::vector <Entity*>& ent) {

	CheckKey();

	if (tp_time > 0)
	    tp_time -= time;

	if (hit_time > 0) {
	    hit_time -= time;
        anim_map_.SetAnimation("hit");
	}
    else {
        hit_time = 0;
        feel_ = Player_feeling::no_hit;

        if (state_ == Player_state::stay)
            anim_map_.SetAnimation("stay");
        if (state_ == Player_state::go)
            anim_map_.SetAnimation("go");
        if (state_ == Player_state::jump)
            anim_map_.SetAnimation("jump");

    }

    anim_map_.ChangeDirection(dir_);

    x_ += dx_ * time / 800;
    Collide('x', obj, ent);

    dy_ += time * 0.00000029;
    y_ += dy_ * time / 800;
    Collide('y', obj, ent);

	KeyReset();
    anim_map_.Tick(time);
}

void Player::Collide(const char d, const std::vector<Object> &obj, const std::vector <Entity*>& ent) {
	
	for (const auto & i : obj)
		if (GetRect().intersects(i.rect)) {

			if (i.type == Object_type::solid)
			{
				if (dy_ > 0 && d == 'y') { y_ = i.rect.top - h_; dy_ = 0; state_ = Player_state::stay; }
				else if (dy_ < 0 && d == 'y') { y_ = i.rect.top + i.rect.height; dy_ = 0; }
				else if (dx_ > 0 && d == 'x') { x_ = i.rect.left - w_; }
				else if (dx_ < 0 && d == 'x') { x_ = i.rect.left + i.rect.width; }
			}
			else if (i.type == Object_type::jumper) {
                dy_ = -0.3;
                state_ = Player_state::jump;
                jump_sound.play();
            }
            else if (i.type == Object_type::tp && tp_time <= 0) {
                std::vector<Object> tps;
                auto it = obj.begin();
                while (it != obj.end()) {

                    auto iter = std::find_if(it, obj.end(), [](const Object& ob) { return ob.type == Object_type::tp; });
                    tps.push_back(*it);
                    if (iter != obj.end())
                        it = iter + 1;
                    else
                        break;
                }

                int i = rand() % tps.size();

                x_ = tps[i].rect.left;
                y_ = tps[i].rect.top;
                tp_time += 1000000;
            }
		}

	for (auto* ent : ent) {

			if (GetRect().intersects(ent->GetRect())) {
                if (ent->GetType() == Entity_type::Coca) {
                    if (feel_ == Player_feeling::no_hit && !ent->GetDead()) {
                        damage_sound.play();
                        feel_ = Player_feeling::hit;
                        health_ -= 1;
                        hit_time = 1500000;
                        hit = true;
                    }

                    if (dy_ > 0 && d == 'y') { state_ = Player_state::jump; dy_ *= -0.5;}
                        ent->Health(-200);
                }
                else if (ent->GetType() == Entity_type::Ghost) {
                    if (feel_ == Player_feeling::no_hit && !ent->GetDead()) {
                        damage_sound.play();
                        feel_ = Player_feeling::hit;
                        health_ -= 1;
                        hit_time = 1500000;

                        if (dy_ > 0 && d == 'y')
                            state_ = Player_state::jump; dy_ *= -0.5;

                        hit = true;
                        ent->Health(-200);
                    }
                }

		}
	}
}