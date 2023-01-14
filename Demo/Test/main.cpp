#include "../../includes/CookieEngine.cpp"
#include "../../includes/GameObject.cpp"
#include "../../includes/Scene.cpp"
#include "../../includes/SpriteRenderer.cpp"
#include "../../includes/Gametime.cpp"

#include <iostream>

using namespace std;

class Player : public GameObject {
public:
    Player() : GameObject(0, 0, 1, "Player") {
        SpriteRenderer* renderer = new SpriteRenderer();
        renderer->SetRectangle(100, 100);
        this->AddChild(renderer);
    }

    void Update() override {
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            this->x += 100 * Gametime::deltaTime;
        }
    }
};

class Scene1 : public Scene {
public:
    Scene1() {
        Player* player = new Player();
        this->AddGameObject(player);
    }
};

int main() {
    CookieEngine e;
    e.InitDisplay();
    e.SetScene(new Scene1());
    e.Run();
    return 0;
}