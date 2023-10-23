#ifndef TURRET4_HPP
#define TURRET4_HPP
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"

class PlayScene;
class Turret4: public Turret {
public:
	static const int Price;
    Turret4(float x, float y);
    void CreateBullet() override;
};
#endif // LASERTURRET_HPP

