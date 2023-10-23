#include "PlayScene.hpp"
#include "character3.hpp"
#include "Bag.hpp"
#include "SuperBag.hpp"
#include "AudioHelper.hpp"

const int character3::health = 100;
character3::character3(float x, float y) :
	// TODO 2 (2/8): You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
	Turret("play/bus.png", x, y, health, 0.9) {
    ultenergy = 70;
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void character3::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point pp;
	pp.x = 2;
	pp.y = 2;
    pp =  pp.Normalize();
	Engine::Point normalized = diff.Normalize();
	Engine::Point diff1,diff2;
	diff1 = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + ALLEGRO_PI / 6), sin(Rotation - ALLEGRO_PI / 2 + ALLEGRO_PI / 6));
	diff2 = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 - ALLEGRO_PI / 6), sin(Rotation - ALLEGRO_PI / 2 - ALLEGRO_PI / 6));
	// Change bullet position to the front of the gun barrel.
	if(ultimate){
		getPlayScene()->BulletGroup->AddNewObject(new SuperBag(Position + normalized * 125, diff, rotation, this));
		getPlayScene()->BulletGroup->AddNewObject(new SuperBag(Position + normalized * 125, diff1, rotation, this));
		getPlayScene()->BulletGroup->AddNewObject(new SuperBag(Position + normalized * 125, diff2, rotation, this));
		ultimate = false;
		AudioHelper::PlayAudio("Yasuo.ogg");
	}
	else{
		getPlayScene()->BulletGroup->AddNewObject(new Bag(Position + normalized * 125, diff, rotation, this));
		AudioHelper::PlayAudio("mundo.ogg");
	}

}
