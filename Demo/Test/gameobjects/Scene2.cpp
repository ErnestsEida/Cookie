#pragma once
#include "../../../includes/Scene.cpp"
#include "Player.cpp"

class Scene2 : public Scene {
public:
    Scene2() {
        // Player *player = new Player();
        // this->AddGameObject(player);
    }
    void SetupScene() {
        Player *player = new Player();
        this->AddGameObject(player);
    }
};