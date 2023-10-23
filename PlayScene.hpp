#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <vector>
#include "IScene.hpp"
#include "Sprite.hpp"
#include "Label.hpp"
#include "Turret.hpp"

class PlayScene final : public Engine::IScene {
private:
	enum TileType {
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
	};
protected:
    int lives;
	int money;
	//int SpeedMult;
public:

	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;

	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	float ticks;
	// Map tiles.
	Group* BackGroundGroup;
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* BulletGroup;
	Group* TowerGroup;
	//Group* EnemyGroup;
	Group* EffectGroup;
	Group* UIGroup;
	Engine::Label* UIMoney;
	Engine::Label* UILives;
	//Engine::Image* imgTarget;
	Turret* player1;
	Turret* player2;
	Engine::Image* black1;
	Engine::Image* red1;
	Engine::Image* energy1;
	Engine::Image* black2;
	Engine::Image* red2;
	Engine::Image* energy2;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<int>> mapDistance;
	//std::list<std::pair<int, float>> enemyWaveData;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void Hit();
	void ReadMap();
	void ConstructUI();
	void UIBtnClicked(int id);
	int character1;
	int character2;
	void PlayOnClick();
};
#endif // PLAYSCENE_HPP
