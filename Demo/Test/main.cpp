#include "../../includes/CookieEngine.cpp"
#include "../../includes/GameObject.cpp"
#include "../../includes/Scene.cpp"
#include "../../includes/SpriteRenderer.cpp"
#include "../../includes/Gametime.cpp"
#include "../../includes/Input.cpp"
#include "../../includes/Animation.cpp"

#include <iostream>

using namespace std;

class Player : public GameObject {
private:
    Animation* runAnimation = new Animation("./sprites/run.png", Vector2i(48, 48), 6, true);
    SpriteRenderer* renderer;

public:
    Player() : GameObject(100, 100, 1, "Player") {
        this->renderer = new SpriteRenderer();
        this->renderer->SetAnimation(this->runAnimation);
        this->renderer->SetOrigin(Origin::Center);
        this->AddChild(renderer);
    }

    void Update() override {
        if (Input::OnKey(Keyboard::Key::D)) {
            this->x += 100 * Gametime::deltaTime;
            this->renderer->SetScale(Vector2f(1, 1));
        } else if (Input::OnKey(Keyboard::Key::A)) {
            this->x -= 100 * Gametime::deltaTime;
            this->renderer->SetScale(Vector2f(-1, 1));
        }

        if (Input::OnKeyDown(Keyboard::Key::F)) {
            this->runAnimation->ToggleFreeze();
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
    e.InitDisplay(1280, 720, "Game");
    e.SetScene(new Scene1());
    e.Run();
    return 0;
}