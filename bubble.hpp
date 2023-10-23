#ifndef BUBBLE_HPP
#define BUBBLE_HPP
#include "Bullet.hpp"
class bubble : public Bullet {
public:
	explicit bubble(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Turret* tur) override;
    //void Update(float deltaTime) override;
};
#endif // FIREBULLET_HPP

