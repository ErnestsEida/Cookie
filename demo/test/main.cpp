#include <iostream>
#include "../../includes/CookieEngine.cpp"
#include "../../includes/Components.hpp"

using namespace std;

class Player : public GameObject {
private:
    bool grounded = false;
    float vsp;
    Animation* idleAnimation = new Animation("./src/idle.png", 48, 48, 5);
    Animation* runAnimation = new Animation("./src/run.png", 48, 48, 6);
    SpriteRenderer* renderer;
    AudioPlayer* player;
    Camera* cam;
public:
    Player(int x, int y, Camera* camera) : GameObject(x, y) {
        player = new AudioPlayer();
        renderer = new SpriteRenderer();
        this->Set_Component(player);
        this->Set_Component(renderer);
        this->cam = camera;
    }

    void Update() override {
        int hsp = (Keyboard::isKeyPressed(Keyboard::Key::D) - Keyboard::isKeyPressed(Keyboard::Key::A)) * 4;
        if (hsp != 0) {
            renderer->SetAnimation(runAnimation);
        } else {
            renderer->SetAnimation(idleAnimation);
        }

        if (!grounded) {
            vsp += 0.1;
        } else {
            vsp = 0;    
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Key::Space) && grounded){
            this->player->ChangeSource("./src/obunga.wav");
            this->player->Play();
            vsp = -4;
            grounded = false;
        }
        
        this->Set_Y(this->Get_Y() + vsp);
        this->Set_X(this->Get_X() + hsp);
        this->cam->SetCenter(this->Get_X(), this->Get_Y());
    }

    void OnCollision(GameObject* other) {
        if (other != NULL) {
            this->grounded = true;
            this->Set_Y(other->Get_Y() - this->Get_Collider()->height);
        }
    }
};

class CollisionBlock : public GameObject {
public:
    CollisionBlock(int x, int y) : GameObject(x, y) {
        GameShape* shape = new GameShape(GameShape::ShapeType::Rectangle, 1280, 10);
        this->Set_Component(shape);
    }
    void Update() override {}
    void OnCollision(GameObject* other) {}
};

int main()
{
    CookieEngine engine;
    engine.InitWindow(1280, 720, "Test Title");

    Player player(10, 10, engine.GetMainCamera());
    player.Set_Collider(50, 37);

    CollisionBlock block(0, 710);
    block.Set_Collider(1280, 10);
    
    engine.Run();
    return 0;
}