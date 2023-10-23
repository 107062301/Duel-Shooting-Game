#include <string>
#include <queue>
#include <fstream>
#include "Image.hpp"
#include "Label.hpp"
#include "ImageButton.hpp"
#include "PlayScene.hpp"
#include "StageSelectScene.hpp"
#include "LOG.hpp"
#include "Enemy.hpp"
#include "PlaneEnemy.hpp"
#include "SoldierEnemy.hpp"
#include "TankEnemy.hpp"
#include "Enemy4.hpp"
#include "Octopus.hpp"
#include "MachineGunTurret.hpp"
#include "character3.hpp"
#include "LaserTurret.hpp"
#include "MissileTurret.hpp"
#include "Turret4.hpp"
#include "TurretButton.hpp"
#include "Plane.hpp"
#include "DirtyEffect.hpp"
#include "AudioHelper.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);
const std::vector<int> PlayScene::code = { ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
									ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
									ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER };
Engine::Point PlayScene::GetClientSize() {
	return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}

void PlayScene::Initialize() {
	// TODO 5 (1/2): There's a bug in this file, which crashes the game when you win. Try to find it.
	// TODO 5 (2/2): There's a cheat code in this file. Try to find it.

	mapState.clear();
	keyStrokes.clear();
	ticks = 0;
	lives = 10;
	money = 150;
	// Add groups from bottom to top.
	AddNewObject(BackGroundGroup = new Group());
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(DebugIndicatorGroup = new Group());
	AddNewObject(TowerGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	// Should support buttons.
	AddNewControlObject(UIGroup = new Group());
	ReadMap();
	ConstructUI();
    TileMapGroup->AddNewObject(new Engine::Image("play/sand3.png", 0, 0, 1600, 832));
    TileMapGroup->AddNewObject(new Engine::Image("play/grey.png", 0, 0, 1600, 120));
    //BackGroundGroup->AddNewObject(new Engine::Image("play/background.png", 0, 0, 1600, 832));
    //TileMapGroup->AddNewObject(new Engine::Image("play/background.png", 0, 0, 500, 500));
	if(character1 == 1){
        TowerGroup->AddNewObject(player1 = new Octopus(50, 170));
        player1->player1=true;
	}
    if(character1 == 2){
        TowerGroup->AddNewObject(player1 = new MachineGunTurret(50, 170));
        player1->player1=true;
    }
    if(character2 == 1){
        TowerGroup->AddNewObject(player2 = new Octopus(1550, 782));
        player2->player2=true;
    }
    if(character2 == 2){
        TowerGroup->AddNewObject(player2 = new MachineGunTurret(1550, 782));
        player2->player2=true;
    }
    if(character1 == 3){
        TowerGroup->AddNewObject(player1 = new character3(50, 170));
        player1->player1=true;
    }
    if(character2 == 3){
        TowerGroup->AddNewObject(player2 = new character3(1550, 782));
        player2->player2=true;
    }
	UIGroup->AddNewObject(black1 = new Engine::Image ("play/black.png", 80, 60, 500, 20));
    UIGroup->AddNewObject(red1 = new Engine::Image ("play/health.png", 80, 60, 500, 20));
    UIGroup->AddNewObject(energy1 = new Engine::Image ("play/energy.png", 80, 85, 1, 20));
    UIGroup->AddNewObject(black2 = new Engine::Image("play/black.png", 1010, 60, 500, 20));
    UIGroup->AddNewObject(red2 = new Engine::Image("play/health.png", 1010, 60, 500, 20));
    UIGroup->AddNewObject(energy2 = new Engine::Image ("play/energy.png", 1010, 85, 1, 20));
	AudioHelper::PlayBGM("mega.ogg");
}
void PlayScene::Update(float deltaTime) {
	// Fake speed up.
	//deltaTime *= SpeedMult;
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	// Reference: Bullet-Through-Paper
	if (deltaTime < 3) {
		IScene::Update(deltaTime);
	} else if (deltaTime < 6) {
		IScene::Update(deltaTime / 2);
		IScene::Update(deltaTime / 2);
	} else if (deltaTime < 9) {
		IScene::Update(deltaTime / 3);
		IScene::Update(deltaTime / 3);
		IScene::Update(deltaTime / 3);
	} else {
		IScene::Update(deltaTime / 4);
		IScene::Update(deltaTime / 4);
		IScene::Update(deltaTime / 4);
		IScene::Update(deltaTime / 4);
	}

	ticks += deltaTime;

        /*delete TileMapGroup;
        delete GroundEffectGroup;
        delete DebugIndicatorGroup;
        delete TowerGroup;
        delete BulletGroup;
        delete EffectGroup;
        delete UIGroup;*/

    if(player1->GetHealth() <= 0)
        Engine::GameEngine::GetInstance().ChangeScene("lose");
    else if(player2->GetHealth() <= 0)
        Engine::GameEngine::GetInstance().ChangeScene("win");



	if(player1->keydown_left||player1->keydown_right){
        if(!player1->walk)
            player1->presskey = true;
        //player1->walk = 0;
	}
	if((player1->keyup_left || player1->keyup_left) && player1->presskey){
        player1->presskey = false;
        //player1->walk = 200;
	}
	if(player2->keydown_left||player2->keydown_right){
        if(!player2->walk)
            player2->presskey = true;
        //player2->walk = 0;
	}
	if((player2->keyup_left || player2->keyup_left) && player2->presskey){
        player2->presskey = false;
        //player2->walk == 200;
	}

    if(player1->onhit){
        UIGroup->RemoveObject(black1->GetObjectIterator());
        UIGroup->RemoveObject(red1->GetObjectIterator());
        UIGroup->RemoveObject(energy1->GetObjectIterator());
        UIGroup->AddNewObject(black1 = new Engine::Image ("play/black.png", 80, 60, 500, 20));
        UIGroup->AddNewObject(red1 = new Engine::Image ("play/health.png", 80, 60, player1->GetHealth()*5, 20));
        UIGroup->AddNewObject(energy1 = new Engine::Image ("play/energy.png", 80, 85, player1->energy*5, 20));
        player1->onhit = false;
    }
    if(player2->onhit){
        UIGroup->RemoveObject(black2->GetObjectIterator());
        UIGroup->RemoveObject(red2->GetObjectIterator());
        UIGroup->RemoveObject(energy2->GetObjectIterator());
        UIGroup->AddNewObject(black2 = new Engine::Image("play/black.png", 1010, 60, 500, 20));
        UIGroup->AddNewObject(red2 = new Engine::Image("play/health.png", 1010, 60, player2->GetHealth()*5, 20));
        UIGroup->AddNewObject(energy2 = new Engine::Image ("play/energy.png", 1010, 85, player2->energy*5, 20));
        player2->onhit = false;
    }

	//auto current = enemyWaveData.front();
	/*if (ticks < current.second)
		return;
	ticks -= current.second;*/
	/*enemyWaveData.pop_front();
	const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize + BlockSize / 2, SpawnGridPoint.y * BlockSize + BlockSize / 2);
	Enemy* enemy;
	switch (current.first) {
	case 1:
		EnemyGroup->AddNewObject(enemy = new SoldierEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
		break;
	case 2:
		EnemyGroup->AddNewObject(enemy = new PlaneEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
		break;
	case 3:
		EnemyGroup->AddNewObject(enemy = new TankEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
		break;
	// TODO 2 (7/8): You need to modify 'resources/enemy1.txt', or 'resources/enemy2.txt' to spawn the 4th enemy.
	//         The format is "[EnemyId] [TimeDelay] [Repeat]".
	case 4:
		EnemyGroup->AddNewObject(enemy = new Enemy4(SpawnCoordinate.x, SpawnCoordinate.y));
		break;
	// TODO 2 (8/8): Enable the creation of the 4th enemy.
	default:
		return;
	}*/
	//enemy->UpdatePath(mapDistance);
	// Compensate the time lost.
	//enemy->Update(ticks);
}
/*void PlayScene::OnMouseDown(int button, int mx, int my) {
	if ((button & 1) && !imgTarget->Visible && preview) {
		// Cancel turret construct.
		UIGroup->RemoveObject(preview->GetObjectIterator());
		preview = nullptr;
	}
	IScene::OnMouseDown(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
	IScene::OnMouseMove(mx, my);
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (!preview || x < 0 || x >= MapWidth || y < 0 || y >= MapHeight) {
		imgTarget->Visible = false;
		return;
	}
	imgTarget->Visible = true;
	imgTarget->Position.x = x * BlockSize;
	imgTarget->Position.y = y * BlockSize;
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
	IScene::OnMouseUp(button, mx, my);
	if (!imgTarget->Visible)
		return;
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (button & 1) {
		if (mapState[y][x] != TILE_OCCUPIED) {
			if (!preview)
				return;
			// Check if valid.
			if (!CheckSpaceValid(x, y)) {
				Engine::Sprite* sprite;
				GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
				sprite->Rotation = 0;
				return;
			}
			// Purchase.
			EarnMoney(-preview->GetPrice());
			// Remove Preview.
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			// Construct real turret.
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2;
			preview->Enabled = true;
			preview->Preview = false;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			TowerGroup->AddNewObject(preview);
			// Remove Preview.
			preview = nullptr;

			mapState[y][x] = TILE_OCCUPIED;
			OnMouseMove(mx, my);
		}
	}
}*/
void PlayScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);

	if (keyCode == ALLEGRO_KEY_Q) {
		player1->keydown_left = true;
		player1->keyup_left = false;

	}
	else if (keyCode == ALLEGRO_KEY_W) {
		player1->keydown_right = true;
		player1->keyup_right = false;
	}
	if (keyCode == ALLEGRO_KEY_E) {
        if(player1->energy - player1->ultenergy < 1){

            //player1->onhit = true;
        }
        else{
            player1->energy -= player1->ultenergy ;
            player1->ultimate = true;
           // player1->uuu = false;
            player1->CreateBullet();
            player1->onhit = true;
        }


	}
	if (keyCode == ALLEGRO_KEY_O) {
		player2->keydown_left = true;
		player2->keyup_left = false;
	}
	else if (keyCode == ALLEGRO_KEY_P) {
		player2->keydown_right = true;
		player2->keyup_right = false;
	}
	if (keyCode == ALLEGRO_KEY_I) {
        if(player2->energy - player2->ultenergy < 1){

            //player1->onhit = true;
        }
        else{
            player2->energy -= player2->ultenergy ;
            player2->ultimate = true;
           // player1->uuu = false;
            player2->CreateBullet();
            player2->onhit = true;
        }


	}
}
void PlayScene::OnKeyUp(int keyCode)
{
    IScene::OnKeyUp(keyCode);

    if (keyCode == ALLEGRO_KEY_Q) {
        if(player1->walk<=0)
		player1->walk = 200;
		player1->keydown_left = false;
		player1->keyup_left = true;

	}
	else if (keyCode == ALLEGRO_KEY_W) {
        if(player1->walk<=0)
		player1->walk = 200;
		player1->keydown_right = false;
		player1->keyup_right = true;

	}
	if (keyCode == ALLEGRO_KEY_O) {
        if(player2->walk<=0)
		player2->walk = 200;
		player2->keydown_left = false;
		player2->keyup_left = true;
	}
	else if (keyCode == ALLEGRO_KEY_P) {
	    if(player2->walk<=0)
		player2->walk = 200;
		player2->keydown_right = false;
		player2->keyup_right = true;
	}
}

/*int PlayScene::GetMoney() const {
	return money;
}
void PlayScene::EarnMoney(int money) {
	this->money += money;
	UIMoney->Text = std::string("$") + std::to_string(this->money);
}*/
void PlayScene::ReadMap() {

	/*std::string filename = std::string("resources/map") + std::to_string(MapId) + ".txt";
	// Read map file.
	char c;
	std::vector<bool> mapData;
	std::ifstream fin(filename);
	while (fin >> c) {
		switch (c) {
		case '0': mapData.push_back(false); break;
		case '1': mapData.push_back(true); break;
		case '\n':
		case '\r':
			if (static_cast<int>(mapData.size()) / MapWidth != 0)
				throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
	}
	fin.close();
	// Validate map data.
	if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
		throw std::ios_base::failure("Map data is corrupted.");
	// Store map in 2d array.
	mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const int num = mapData[i * MapWidth + j];
			mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
			if (num)
				TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
			else
				TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
		}
	}*/
}

void PlayScene::ConstructUI() {
	// Background
	//UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));

	//AddNewObject(new Engine::Label("pvp", "pirulen.ttf", 48, 10, 10, 255, 0, 0, 255, 0, 0));
	//UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 30, 1294, 0));
	//UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
	//UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 48));
	//UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 88));
	/*TurretButton* btn;
	// Button 1
	btn = new TurretButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-1.png", 1294, 136 - 8, 0, 0, 0, 0)
		, 1294, 136, MachineGunTurret::Price);
	// Reference: Class Member Function Pointer and std::bind.
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 2
	btn = new TurretButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-2.png", 1370, 136 - 8, 0, 0, 0, 0)
		, 1370, 136, LaserTurret::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// Button 3
	btn = new TurretButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-3.png", 1446, 136, 0, 0, 0, 0)
		, 1446, 136, MissileTurret::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
	// TODO 2 (3/8): Create a button to support constructing the 4th tower.
	btn = new TurretButton("play/floor.png", "play/dirt.png",
		Engine::Sprite("play/tower-base.png", 1522, 136, 0, 0, 0, 0),
		Engine::Sprite("play/turret-4.png", 1522, 136, 0, 0, 0, 0)
		, 1522, 136, Turret4::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);*/
}

void PlayScene::UIBtnClicked(int id) {
	/*if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
	if (id == 0 && money >= MachineGunTurret::Price)
		preview = new MachineGunTurret(0, 0);
	else if (id == 1 && money >= LaserTurret::Price)
		preview = new LaserTurret(0, 0);
	else if (id == 2 && money >= MissileTurret::Price)
		preview = new MissileTurret(0, 0);
    else if (id == 3 && money >= Turret4::Price)
		preview = new Turret4(0, 0);
	// TODO 2 (4/8): On callback, create the 4th tower.
	if (!preview)
		return;
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);*/
}

/*bool PlayScene::CheckSpaceValid(int x, int y) {
	if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
		return false;
	auto map00 = mapState[y][x];
	mapState[y][x] = TILE_OCCUPIED;
	//std::vector<std::vector<int>> map = CalculateBFSDistance();
	mapState[y][x] = map00;
	if (map[0][0] == -1)
		return false;
	for (auto& it : EnemyGroup->GetObjects()) {
		Engine::Point pnt;
		pnt.x = floor(it->Position.x / BlockSize);
		pnt.y = floor(it->Position.y / BlockSize);
		if (pnt.x < 0 || pnt.x >= MapWidth || pnt.y < 0 || pnt.y >= MapHeight)
			continue;
		if (map[pnt.y][pnt.x] == -1)
			return false;
	}
	// All enemy have path to exit.
	mapState[y][x] = TILE_OCCUPIED;
	mapDistance = map;
	for (auto& it : EnemyGroup->GetObjects())
		dynamic_cast<Enemy*>(it)->UpdatePath(mapDistance);
	return true;
}*/
