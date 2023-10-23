#ifndef TURRET4BULLET_HPP
#define TURRET4BULLET_HPP
#include "Bullet.hpp"
class Turret4Bullet : public Bullet {
public:
	explicit Turret4Bullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Turret* tur) override;
};
#endif // LASERBULLET_HPP
