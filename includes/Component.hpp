#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Component {
private:
    vector<Transformable*> drawables;
public:
    vector<Transformable*> GetDrawables() const{
        return this->drawables;
    }

    void AddDrawable(Transformable* drawable) {
        this->drawables.push_back(drawable);
    }

    void ClearDrawables() {
        this->drawables.clear();
    }

    virtual void Trigger() = 0;
};