#ifndef OCTOPUS_HPP
#define OCTOPUS_HPP
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"

class PlayScene;
class Octopus: public Turret {
public:
	static const int health;
    Octopus(float x, float y);
	void CreateBullet() override;
};
#endif // MACHINEGUNTURRET_HPP



