#include <iostream>
#include "../../includes/CookieEngine.cpp"

using namespace std;

class Player : public GameObject {
private:
    bool grounded = false;
    float vsp;
    Animation* idleAnimation = new Animation("./src/idle.png", 48, 48, 5);
    Animation* runAnimation = new Animation("./src/run.png", 48, 48, 6);
public:
    Player(int x, int y) : GameObject(x, y) {}

    void Update() override {
        int hsp = (Keyboard::isKeyPressed(Keyboard::Key::D) - Keyboard::isKeyPressed(Keyboard::Key::A)) * 4;
        if (hsp != 0) {
            Set_Animation(runAnimation);
        } else {
            Set_Animation(idleAnimation);
        }
        if (!grounded) {
            vsp += 0.1;
        } else {
            vsp = 0;    
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Space) && grounded){
            vsp = -4;
            grounded = false;
        }
        
        this->Set_Y(this->Get_Y() + vsp);
        this->Set_X(this->Get_X() + hsp);
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
    CollisionBlock(int x, int y) : GameObject(x, y) {}
    void Update() override {}
    void OnCollision(GameObject* other) {} 
};

int main()
{
    Player player(10, 10);
    player.Set_Collider(50, 37);

    CollisionBlock block(0, 710);
    RectangleShape *r_shape = new RectangleShape(Vector2f(1280, 10));
    block.InsertDrawable(r_shape);
    block.Set_Collider(1280, 10);

    CookieEngine engine;
    engine.InitWindow(1280, 720, "Test Title");
    engine.Run();
    return 0;
}