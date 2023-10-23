#ifndef ULTBUBBLE_HPP
#define ULTBUBBLE_HPP
#include "Bullet.hpp"
class ultbubble : public Bullet {
public:
	explicit ultbubble(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Turret* tur) override;
    //void Update(float deltaTime) override;
};
#endif // FIREBULLET_HPP

