#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Alerts.cpp"

using namespace sf;
using namespace std;

class GameObject {
protected:
    void setParent(GameObject* gameObject) { this->parent = gameObject; }
    void childUpdate() {
        Vector2i currentPos = Vector2i(this->x, this->y);
        Vector2i newPos = Vector2i(this->parent->getX() + this->mirrorX, this->parent->getY() + this->mirrorY);
        this->x = newPos.x - currentPos.x;
        this->y = newPos.y - currentPos.y;
    }
    void changeIsChild(bool value) { this->isChild = value; }
private:
    int x, y, mirrorX, mirrorY;
    float z;
    string objectName, tag;
    IntRect collider;
    bool isChild = false;
    GameObject* parent = NULL;

    vector<GameObject*> children;
    vector<Drawable*> drawables;
public:
    // STATIC
    static int objectCount;
    static vector<GameObject*> objects;

    static vector<GameObject*> getAllObjects();
    static vector<GameObject*> getParentObjects();
    static vector<GameObject*> getChildObjects();
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
    void setX(int x) { this->x = x; this->mirrorX = x; }
    void setY(int y) { this->y = y; this->mirrorY = y; }
    void setZ(int z) { this->z = z; }
    void setObjectName(string objectName) { this->objectName = objectName; }
    void setTag(string tag) { this->tag = tag; }
    void setChildren(vector<GameObject*> children) { this->children = children; }
    void setCollider(int width, int height) { this->collider = IntRect(this->x, this->y, width, height); }

    // ADDING
    void addChild(GameObject* child) {
        child->changeIsChild(true);
        child->setY(this->y + child->getY());
        child->setX(this->x + child->getX());
        child->setParent(this);
        this->children.push_back(child); 
    }
    void addDrawable(Drawable* drawable) { this->drawables.push_back(drawable); }

    // MISC
    void UpdateChildren() {
        for(int i = 0; i < this->children.size(); i++){
            this->children[i]->childUpdate();
        }
    }

    void UpdateComponents() {
        Transformable* asTransformable;
        for(int i = 0; i < this->drawables.size(); i++) {
            asTransformable = dynamic_cast<Transformable*>(this->drawables[i]);
            asTransformable->setPosition(this->x, this->y);
        }

        this->collider.left = this->x;
        this->collider.top = this->y;
    }

    // Virtual
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
};