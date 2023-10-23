#ifndef BANANABULLET_HPP
#define BANANABULLET_HPP
#include "Bullet.hpp"
class BananaBullet : public Bullet {
public:
	explicit BananaBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) ;

};
#endif // FIREBULLET_HPP
