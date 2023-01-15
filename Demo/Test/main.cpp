#include "../../includes/CookieEngine.cpp"
#include "../../includes/GameObject.cpp"
#include "../../includes/Scene.cpp"
#include "../../includes/SpriteRenderer.cpp"
#include "../../includes/Gametime.cpp"
#include "../../includes/Input.cpp"
#include "../../includes/Animation.cpp"
#include "../../includes/Collider.cpp"

#include <iostream>

using namespace std;

class Player : public GameObject {
private:
    Animation* runAnimation = new Animation("./sprites/run.png", Vector2i(48, 48), 6, true);
    SpriteRenderer* renderer;
    Collider* collider;

public:
    Player() : GameObject(100, 100, 1, "Player", "player") {
        this->renderer = new SpriteRenderer();
        this->renderer->SetAnimation(this->runAnimation);
        this->renderer->SetOrigin(Origin::Center);

        this->collider = new Collider(Vector2f(24, 38));
        
        this->AddChild(this->collider);
        this->AddChild(renderer);
    }

    void Update() override {
        float hsp = 0;
        if (Input::OnKey(Keyboard::Key::D)) {
            hsp += 100 * Gametime::deltaTime;
            this->renderer->SetScale(Vector2f(1, 1));
        } else if (Input::OnKey(Keyboard::Key::A)) {
            hsp -= 100 * Gametime::deltaTime;
            this->renderer->SetScale(Vector2f(-1, 1));
        }
        this->x += hsp;

        if (Input::OnKeyDown(Keyboard::Key::Escape)) {
            CookieEngine::singleton->CloseGame();
        }
    }
};

class Block : public GameObject {
private:
    Collider* collider;
public:
    Block(float x, float y) : GameObject(x, y, z, "Block", "block") {
        collider = new Collider(Vector2f(50, 50), true);
        this->AddChild(collider);
    }

    void Update() override {}
};

class Scene1 : public Scene {
public:
    Scene1() {
        Player* player = new Player();
        this->AddGameObject(player);
        this->AddGameObject(new Block(300, 100));
    }
};

int main() {
    CookieEngine e;
    e.InitDisplay(1280, 720, "Game");
    e.SetScene(new Scene1());
    e.Run();
    return 0;
}