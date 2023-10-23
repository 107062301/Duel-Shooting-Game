#ifndef SUPERBAG_HPP
#define SUPERBAG_HPP
#include "Bullet.hpp"
class SuperBag : public Bullet {
public:
	explicit SuperBag(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) ;
};
#endif // FIREBULLET_HPP
