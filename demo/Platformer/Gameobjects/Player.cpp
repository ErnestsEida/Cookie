#include "../includes/GameObject.hpp"
#include <iostream>

using namespace std;

class Player : public GameObject {
public:
    Player(float x, float y) : GameObject(x, y) {
        this->setCollider(64, 128);
        RectangleShape* shape = new RectangleShape(Vector2f(64, 128));
        shape->setFillColor(Color::Green);
        this->addDrawable(shape);
    }

    void OnStart() override {}

    void OnUpdate() override {
        cout << "Player Created" << endl;
    }
};