#include "StageSelectScene.hpp"
#include "PlayScene.hpp"
#include "AudioHelper.hpp"
#include "Slider.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    player1 = player2 = 0;
    PlayScene*scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->character1 = 0;
    scene->character2 = 0;
    Engine::ImageButton* btn;
    AddNewObject(new Engine::Image ("stage-select/main.png", 0, 0, 1600, 832));
    AddNewObject(new Engine::Label("Select Your Character", "thick.ttf", 60, halfW, 75, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Player 1", "thick.ttf", 60, 320, 170, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Player 2", "thick.ttf", 60, halfW + 510, 170, 255, 255, 255, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("stage-select/octopus.png", "stage-select/octopus2.png", 100, 250, 100, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 11));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/octopus.png", "stage-select/octopus2.png", halfW + 290, 250, 100, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 21));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/monkey.png", "stage-select/monkey2.png", 250, 250, 100, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 12));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/monkey.png", "stage-select/monkey2.png", halfW + 440, 250, 100, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 22));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/bus.png", "stage-select/bus2.png", 400, 250, 100, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 13));
    AddNewControlObject(btn);

    btn = new Engine::ImageButton("stage-select/bus.png", "stage-select/bus2.png", halfW + 590, 250, 100, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 23));
    AddNewControlObject(btn);


    btn = new Engine::ImageButton("stage-select/startbutton.png", "stage-select/startbutton2.png", halfW - 150, 600, 300, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 00));
    AddNewControlObject(btn);

    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(450, 800, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&StageSelectScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 400, 800, 255, 255, 255, 255, 0.5, 0.5));
    sliderSFX = new Slider(halfW + 200, 800, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&StageSelectScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, halfW + 150, 800, 255, 255, 255, 255, 0.5, 0.5));
    // Not a safe way, however we only free while change scene, so it's fine.
    bgmInstance = al_create_sample_instance(Engine::Resources::GetInstance().GetSample("select.ogg").get());
    al_set_sample_instance_playmode(bgmInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgmInstance, al_get_default_mixer());
    al_play_sample_instance(bgmInstance);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}
void StageSelectScene::PlayOnClick(int choice) {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if(choice == 11){
        if(scene->character1 == 2)
            RemoveObject(monk1->GetObjectIterator());
        else if(scene->character1 == 3)
            RemoveObject(nerd1->GetObjectIterator());
        else if(scene->character1 == 1)
            return;
        player1 = true;
        scene->character1 = 1;
        AddNewObject(octo1 = new Engine::Image ("play/octopus.png", 320, 550, 0, 0, 0.5, 0.5));
    }
    else if(choice == 12){
        if(scene->character1 == 1)
            RemoveObject(octo1->GetObjectIterator());
        else if(scene->character1 == 3)
            RemoveObject(nerd1->GetObjectIterator());
        else if(scene->character1 == 2)
            return;
        player1 = true;
        scene->character1 = 2;
        AddNewObject(monk1 = new Engine::Image ("play/monkey4.png", 320, 550, 0, 0, 0.5, 0.5));
    }
    else if(choice == 21){
        if(scene->character2 == 2)
            RemoveObject(monk2->GetObjectIterator());
        else if(scene->character2 == 3)
            RemoveObject(nerd2->GetObjectIterator());
        else if(scene->character2 == 1)
            return;
        player2 = true;
        scene->character2 = 1;
        AddNewObject(octo2 = new Engine::Image ("play/octopus.png", halfW + 510, 550, 0, 0, 0.5, 0.5));
    }
    else if(choice == 22){
        if(scene->character2 == 1)
            RemoveObject(octo2->GetObjectIterator());
        else if(scene->character2 == 3)
            RemoveObject(nerd2->GetObjectIterator());
        else if(scene->character2 == 2)
            return;
        player2 = true;
        scene->character2 = 2;
        AddNewObject(monk2 = new Engine::Image ("play/monkey4.png", halfW + 510, 550, 0, 0, 0.5, 0.5));
    }
    else if(choice == 13){
        if(scene->character1 == 1)
            RemoveObject(octo1->GetObjectIterator());
        else if(scene->character1 == 2)
            RemoveObject(monk1->GetObjectIterator());
        else if(scene->character1 == 3)
            return;
        player1 = true;
        scene->character1 = 3;
        AddNewObject(nerd1 = new Engine::Image ("play/bus.png", 320, 550, 0, 0, 0.5, 0.5));
    }
    else if(choice == 23){
        if(scene->character2 == 1)
            RemoveObject(octo2->GetObjectIterator());
        else if(scene->character2 == 2)
            RemoveObject(monk2->GetObjectIterator());
        else if(scene->character2 == 3)
            return;
        player2 = true;
        scene->character2 = 3;
        AddNewObject(nerd2 = new Engine::Image ("play/bus.png", halfW + 510, 550, 0, 0, 0.5, 0.5));
    }
    if((player1 && player2) && choice == 00)
        Engine::GameEngine::GetInstance().ChangeScene("play");
}
void StageSelectScene::BGMSlideOnValueChanged(float value) {
    al_set_sample_instance_gain(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void StageSelectScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}

