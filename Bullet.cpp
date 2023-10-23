#include "Sprite.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include "Turret.hpp"
#include "Bullet.hpp"
#include "LOG.hpp"
#include "DirtyEffect.hpp"

PlayScene* Bullet::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Bullet::OnExplode(Turret* tur) {
}
Bullet::Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) {
	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;
	CollisionRadius = 4;
}
void Bullet::Update(float deltaTime) {
    if(spin == true)
        Rotation += ALLEGRO_PI / 5;
    if(spin3 == true)
        Rotation += ALLEGRO_PI / 20;

     if(spin2 == true)
        Rotation += ALLEGRO_PI / 10;

	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();

    if(bounce){
        if(Position.x<=0 || Position.x>=1600){
            Velocity.x = -Velocity.x;
            counter --;
            if(counter == -1){
                getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            }

        }
        if(Position.y<=120 || Position.y>=832){
            Velocity.y = -Velocity.y;
            counter --;
            if(counter == -1){
                getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            }
        }
    }
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
	for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* tur = dynamic_cast<Turret*>(it);
		if (tur == parent)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, tur->Position, tur->CollisionRadius)) {
			OnExplode(tur);
            if(tur->player1&&bouncebullet1){}
            if(tur->player2&&bouncebullet2){}
            else
            tur->Hit(damage,ultbullet);

			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), Engine::Point(1600, 832)))
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
