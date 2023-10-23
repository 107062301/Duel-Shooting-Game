#include "PlayScene.hpp"
#include "bubble.hpp"
#include "ultbubble.hpp"
#include "Octopus.hpp"
#include "AudioHelper.hpp"

const int Octopus::health = 100;
Octopus::Octopus(float x, float y) :
	Turret("play/octopus.png", x, y, health, 0.7) {
    ultenergy = 30;
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Octopus::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	if(ultimate == false){
        getPlayScene()->BulletGroup->AddNewObject(new bubble(Position + normalized * 150, diff, rotation, this));
        getPlayScene()->BulletGroup->AddNewObject(new bubble(Position + normalized * 175, diff, rotation, this));
        getPlayScene()->BulletGroup->AddNewObject(new bubble(Position + normalized * 200, diff, rotation, this));
        AudioHelper::PlayAudio("gun.wav");
	}
	else{
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + normalized * 150, diff, rotation, this));
        diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + 2*ALLEGRO_PI / 8), sin(Rotation - ALLEGRO_PI / 2 + 2*ALLEGRO_PI / 8));
        rotation = atan2(diff.y, diff.x);
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + normalized * 150, diff, rotation, this));
        diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + 2*2*ALLEGRO_PI / 8), sin(Rotation - ALLEGRO_PI / 2 + 2*2*ALLEGRO_PI / 8));
        rotation = atan2(diff.y, diff.x);
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + diff * 150 + diff, diff, rotation, this));
        diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + 3*2*ALLEGRO_PI / 8), sin(Rotation - ALLEGRO_PI / 2 + 3*2*ALLEGRO_PI / 8));
        rotation = atan2(diff.y, diff.x);
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + diff * 150, diff, rotation, this));
        diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + 4*2*ALLEGRO_PI / 8), sin(Rotation - ALLEGRO_PI / 2 + 4*2*ALLEGRO_PI / 8));
        rotation = atan2(diff.y, diff.x);
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + diff * 150, diff, rotation, this));
        diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + 5*2*ALLEGRO_PI / 8), sin(Rotation - ALLEGRO_PI / 2 + 5*2*ALLEGRO_PI / 8));
        rotation = atan2(diff.y, diff.x);
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + diff * 150, diff, rotation, this));
        diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + 6*2*ALLEGRO_PI / 8), sin(Rotation - ALLEGRO_PI / 2 + 6*2*ALLEGRO_PI / 8));
        rotation = atan2(diff.y, diff.x);
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + diff*150, diff, rotation, this));
        diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + 7*2*ALLEGRO_PI / 8), sin(Rotation - ALLEGRO_PI / 2 + 7*2*ALLEGRO_PI / 8));
        rotation = atan2(diff.y, diff.x);
        getPlayScene()->BulletGroup->AddNewObject(new ultbubble(Position + diff * 150, diff, rotation, this));
        ultimate = false;
    }
}


