#include "SuperBag.hpp"
#include "DirtyEffect.hpp"

SuperBag::SuperBag(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bag.png", 1100,20, position, forwardDirection, rotation - ALLEGRO_PI, parent) {
	bounce = true;
	spin = true;
	superbag = true;
	ultbullet = true;
	// TODO 2 (1/8): You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}
void SuperBag::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

