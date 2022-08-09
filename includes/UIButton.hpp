#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "./UIObject.cpp"

using namespace sf;
using namespace std;

class UIButton : public UIObject{
public:
    UIButton(int x, int y) : UIObject(x, y) {
        RectangleShape* rect = new RectangleShape(Vector2f(200, 100));
        this->AddDrawable(rect);
        this->SetCollider(200, 100);
    }

    void MouseOnHover() override {};
    void MouseOnEnter() override {cout << "Enter" << endl;};
    void MouseOnExit() override {cout << "Exit" << endl;};
};