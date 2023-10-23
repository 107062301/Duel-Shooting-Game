#include "Turret4Bullet.hpp"
#include "DirtyEffect.hpp"

Turret4Bullet::Turret4Bullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-2.png", 800, 2, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void Turret4Bullet::OnExplode(Turret* tur) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 10);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-2.png", dist(rng), tur->Position.x, tur->Position.y));
}
