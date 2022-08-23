#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Alerts.cpp"

using namespace sf;
using namespace std;

class GameObject {
private:
    int x, y;
    float z;
    string objectName, tag;
    IntRect collider;
    bool isChild = false;

    vector<GameObject*> children;
    vector<Drawable*> drawables;
public:
    // STATIC
    static int objectCount;
    static vector<GameObject*> objects;
    static void SortObjectsByZ();

    // CONSTRUCTORS
    GameObject(int x, int y);
    
    GameObject(int x, int y, float z);
    
    GameObject(int x, int y, float z, string objectName);
    
    GameObject(int x, int y, float z, string objectName, string tag);

    // GETTERS
    int getX() const { return this->x; }
    int getY() const { return this->y; }
    float getZ() const { return this->z; }
    string getObjectName() const { return this->objectName; }
    string getTag() const { return this->tag; }
    vector<GameObject*> getChildren() { return this->children; }
    vector<Drawable*> getDrawables() const { return this->drawables; }
    IntRect getCollider() const { return this->collider; }

    // SETTERS
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setZ(int z) { this->z = z; }
    void setObjectName(string objectName) { this->objectName = objectName; }
    void setTag(string tag) { this->tag = tag; }
    void setChildren(vector<GameObject*> children) { this->children = children; }
    void setCollider(int width, int height) { this->collider = IntRect(this->x, this->y, width, height); }

    // ADDING
    void addChild(GameObject* child) {
        this->changeIsChild(true);
        this->children.push_back(child); 
    }
    void addDrawable(Drawable* drawable) { this->drawables.push_back(drawable); }

    // MISC
    void UpdateChildren() {
        for(int i = 0; i < this->children.size(); i++){
        }
    }

    void changeIsChild(bool value) { this->isChild = value; }

    // Virtual
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
};