#pragma once
#include "../../../includes/Scene.cpp"
#include "./Player.cpp"
#include "./Block.cpp"

class Scene1 : public Scene {
public:
    Scene1() {
    }

    void SetupScene() override {
        Player* player = new Player();
        this->AddGameObject(player);
        this->AddGameObject(new Block(300, 100));
    }
};