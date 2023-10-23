#ifndef STAGESELECTSCENE_HPP
#define STAGESELECTSCENE_HPP
#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"
#include "PlayScene.hpp"
class StageSelectScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_INSTANCE* bgmInstance;
public:
	explicit StageSelectScene() = default;
	void Initialize() override;
	void PlayOnClick(int stage);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
	bool player1;
	bool player2;
	Engine::Image* octo1;
	Engine::Image* octo2;
	Engine::Image* monk1;
	Engine::Image* monk2;
	Engine::Image* nerd1;
	Engine::Image* nerd2;
};

#endif // STAGESELECTSCENE_HPP
