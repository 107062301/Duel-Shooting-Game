#ifndef TURRET_HPP
#define TURRET_HPP
#include "Sprite.hpp"
#include "PlayScene.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Point.hpp"

class PlayScene;
class Bullet;
class Enemy;
class Turret: public Engine::Sprite {
protected:
    int collideDamage;
    float speed;
    int health;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    float current_rotation;
    Sprite img;
    PlayScene* getPlayScene();


public:
    bool player1 = false;
    bool player2 = false;
    bool bus = false;
    bool use = false ;
    bool ultimate = false;
    virtual void CreateBullet() = 0;
    int energy;
    int ultenergy;
    int walk;
    bool ondash = false;
    bool presskey = false;
    bool keydown_right = false;
    bool keydown_left = false;
    bool keyup_right = true;
    bool keyup_left = true;
    bool onhit = false;
    Turret(std::string img, float x, float y, int health,float coolDown);
    void Update(float deltaTime) override;
    void Hit(float damage,bool ult);
	int GetHealth() const;
	virtual void OnExplode();
    // Reference: Design Patterns - Factory Method.
};
#endif // TURRET_HPP
