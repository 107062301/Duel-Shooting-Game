#include <allegro5/allegro_primitives.h>
#include "GameEngine.hpp"
#include "PlayScene.hpp"
#include "ExplosionEffect.hpp"
#include "DirtyEffect.hpp"
#include "Turret.hpp"
#include "AudioHelper.hpp"

PlayScene* Turret::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Turret::Turret(std::string img, float x, float y, int health, float coolDown) :
	Sprite(img, x, y), health(health), img(img, x, y), coolDown(coolDown), walk(0), energy(0) {
    CollisionRadius = Size.x;
    collideDamage = 10;
}
void Turret::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
void Turret::Hit(float damage,bool ult) {
    for (auto& it : getPlayScene()->TowerGroup->GetObjects()) {
		if(it == this) continue;
		Turret* tur = dynamic_cast<Turret*>(it);
		if(!ult){
            if(tur->energy + 20 >= 100)
                tur->energy = 100;
            else
                tur->energy += 20;
            tur->onhit = true;
		}
    }
	health -= damage*0.5;
	if(energy + 10 >= 100)
            energy = 100;
		else
            energy += 10;
	onhit = true;
	OnExplode();
	if(energy <= 0)
        energy = 0;

	if (health <= 0) {
		health = 0;
		// Remove all turret's reference to target.
		/*getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);*/
		AudioHelper::PlayAudio("explosion.wav");
	}
}
void Turret::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	img.Position = Position;
	img.Tint = Tint;

	///energy
	if(energy >= 100)
        energy = 100;
	///player collide
	if(walk > 0 && Velocity.x > 0 && Velocity.y  > 0){
        for (auto& it : scene->TowerGroup->GetObjects()) {
            if(it == this) continue;
            Turret* tur = dynamic_cast<Turret*>(it);
            if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius/1.5, tur->Position, tur->CollisionRadius/1.5)) {
                tur->Hit(collideDamage,false);
                Hit(collideDamage,false);
                tur->Velocity.x = 0;
                tur->Velocity.y = 0;
                Velocity.x = 0;
                Velocity.y = 0;
                walk = 0;
                return;
            }
        }
	}

	///Map Bounds
    int width = GetBitmapWidth();
    int height = GetBitmapHeight();
    if(Position.x - Size.x / 2 < 0)
        Position.x = Size.x / 2;
    else if(Position.x + Size.x / 2 > 1600)
        Position.x = 1600 - Size.x / 2;
    if(Position.y - Size.y / 2 < 120)
        Position.y = Size.y / 2 + 120;
    else if(Position.y + Size.y / 2 > 832)
        Position.y = 832 - Size.y / 2;

	///Movement Control
    if((keydown_left || keydown_right) && !walk){
        if(keydown_right)
            Rotation += ALLEGRO_PI / 20;
        else
            Rotation -= ALLEGRO_PI / 20;
        speed = 1000;
    }
    if(walk <= 0){
        ondash = false;
        Velocity.x = 0;
        Velocity.y = 0;
    }

    if(walk > 0){
        ondash = true;
        walk -= 10;
        speed -= 30;
        Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
        Velocity = diff.Normalize() * speed;
        if(reload >= 0)
            reload -= 0.035;
        if (reload <= 0) {
            reload = coolDown;
            CreateBullet();
        }
    }

}
/*void Turret::Draw() const {
	if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}
	img.Draw();
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw target radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
	}
}*/
int Turret::GetHealth() const {
	return health;
}

