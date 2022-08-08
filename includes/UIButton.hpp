#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "./UIObject.cpp"

using namespace sf;
using namespace std;

class UIButton : public UIObject{
public:
    UIButton(int x, int y) : UIObject(x, y) {
        RectangleShape* rect = new RectangleShape(Vector2f(500, 500));
        this->AddDrawable(rect);
        this->SetCollider(500, 500);
    }

    void MouseOnHover() override {cout << "Hovering..." << endl;};
    void MouseOnEnter() override {cout << "Enter" << endl;};
    void MouseOnExit() override {cout << "Exit" << endl;};
};