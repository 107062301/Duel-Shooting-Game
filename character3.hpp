#ifndef CHARACTER3_HPP
#define CHARACTER3_HPP
#include "PlayScene.hpp"
#include "Bullet.hpp"
#include "Turret.hpp"

class PlayScene;
class character3: public Turret {
public:
	static const int health;
    character3(float x, float y);
	void CreateBullet() override;
};
#endif // MACHINEGUNTURRET_HPP
