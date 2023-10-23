#include "PlayScene.hpp"
#include "MachineGunTurret.hpp"
#include "FireBullet.hpp"
#include "BananaBullet.hpp"
#include "AudioHelper.hpp"

const int MachineGunTurret::health = 100;
MachineGunTurret::MachineGunTurret(float x, float y) :
	// TODO 2 (2/8): You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
	Turret("play/monkey4.png", x, y, health, 0.9) {
    ultenergy = 70;
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void MachineGunTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	Engine::Point diff1,diff2;
	diff1 = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 + ALLEGRO_PI / 6), sin(Rotation - ALLEGRO_PI / 2 + ALLEGRO_PI / 6));
	diff2 = Engine::Point(cos(Rotation - ALLEGRO_PI / 2 - ALLEGRO_PI / 6), sin(Rotation - ALLEGRO_PI / 2 - ALLEGRO_PI / 6));
	// Change bullet position to the front of the gun barrel.
	if(ultimate){
        getPlayScene()->BulletGroup->AddNewObject(new BananaBullet(Position + normalized * 150, diff, rotation, this));
        ultimate = false;
        AudioHelper::PlayAudio("yell.ogg");
	}
	else{
	getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 120, diff1, rotation, this));
	getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 120, diff2, rotation, this));
	getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 120, diff, rotation, this));
	AudioHelper::PlayAudio("monkeyyell.ogg");
	}


}
