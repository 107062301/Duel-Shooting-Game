#ifndef FIREBULLET_HPP
#define FIREBULLET_HPP
#include "Bullet.hpp"
class FireBullet : public Bullet {
public:
	explicit FireBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Turret* tur) override;
    //void Update(float deltaTime) override;
};
#endif // FIREBULLET_HPP
