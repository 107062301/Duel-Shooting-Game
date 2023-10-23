#ifndef BAG_HPP
#define BAG_HPP
#include "Bullet.hpp"
class Bag : public Bullet {
public:
	explicit Bag(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) ;
};
#endif // FIREBULLET_HPP
