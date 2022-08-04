#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Camera {
private:
    View* view;
public:
    Camera(int width, int height) {
        this->view = new View(Vector2f(0, 0), Vector2f(width, height));
    }

    View* GetView() const {
        return this->view;
    }

    void Move(int x, int y) {
        this->view->move(Vector2f(x, y));
    }

    void SetCenter(int x, int y) {
        this->view->setCenter(Vector2f(x, y));
    }

    void SetSize(float width, float height) {
        this->view->setSize(Vector2f(width, height));
    }
};