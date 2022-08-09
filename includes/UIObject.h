#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class UIObject {
private:
    int constant_x, constant_y;
    int x, y, z;
    vector<Transformable*> drawables;
    bool mouse_inside = false;
    IntRect* collider = NULL;
public:
    static vector<UIObject*> objects;

    UIObject(int x, int y);
    UIObject(int x, int y, int z);

    void AddDrawable(Transformable* drawable);
    void SetCollider(int width, int height);

    vector<Transformable*> GetDrawables() const;

    void Update(RenderWindow* window);
    void SyncDrawables(int relative_x, int relative_y);

    virtual void MouseOnEnter() = 0;
    virtual void MouseOnHover() = 0;
    virtual void MouseOnExit() = 0;
};