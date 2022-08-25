#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Alerts.cpp"
#include "Collider.hpp"

using namespace sf;
using namespace std;

class GameObject {
protected:
    void setParent(GameObject* gameObject) { this->parent = gameObject; }
    void childUpdate() {
        Vector2i currentPos = Vector2i(this->x, this->y);
        Vector2i newPos = Vector2i(this->parent->getX() + this->mirrorX, this->parent->getY() + this->mirrorY);
        this->x += (newPos.x - currentPos.x);
        this->y += (newPos.y - currentPos.y);
        this->UpdateComponents();
    }
    void changeIsChild(bool value) { this->isChild = value; }

private:
    float x, y, mirrorX, mirrorY;
    float z;
    string objectName, tag;
    Collider* collider;
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
    GameObject(float x, float y);
    
    GameObject(float x, float y, float z);
    
    GameObject(float x, float y, float z, string objectName);
    
    GameObject(float x, float y, float z, string objectName, string tag);

    // GETTERS
    float getX() const { return this->x; }
    float getY() const { return this->y; }
    float getZ() const { return this->z; }
    string getObjectName() const { return this->objectName; }
    string getTag() const { return this->tag; }
    vector<GameObject*> getChildren() { return this->children; }
    vector<Drawable*> getDrawables() const { return this->drawables; }
    Collider* getCollider() const { return this->collider; }

    // SETTERS
    void setX(float x) { this->x = x; this->mirrorX = x; }
    void setY(float y) { this->y = y; this->mirrorY = y; }
    void setZ(float z) { this->z = z; }
    void setObjectName(string objectName) { this->objectName = objectName; }
    void setTag(string tag) { this->tag = tag; }
    void setChildren(vector<GameObject*> children) { this->children = children; }
    void setCollider(float width, float height) { 
        this->collider = new Collider(width, height);
        this->collider->setHolder(this);
    }

    // ADDING
    void addChild(GameObject* child) {
        child->changeIsChild(true);
        child->setParent(this);
        this->children.push_back(child);
    }
    void addDrawable(Drawable* drawable) { this->drawables.push_back(drawable); }

    // MISC
    GameObject* isColliding(string collision_tag = "") {
        vector<GameObject*> gameobjects = GameObject::objects;
        for(int i = 0;i < gameobjects.size(); i++) {
            if (gameobjects[i] != this && (gameobjects[i]->getTag() == collision_tag || collision_tag == "")) {
                if (this->collider->getArea()->intersects(*gameobjects[i]->getCollider()->getArea())){
                    return gameobjects[i];
                }
            }
        }
        return NULL;
    }

    static GameObject* isCollidingAtPoint(float x, float y, string collision_tag = "") {
        vector<GameObject*> gameobjects = GameObject::objects;
        for(int i = 0; i < gameobjects.size(); i++){
            if (collision_tag == gameobjects[i]->getTag() || collision_tag == ""){
                if (gameobjects[i]->getCollider()->getArea()->contains(x, y)) {
                    return gameobjects[i];
                }
            }
        }
        return NULL;
    }

    void Move(float x, float y) {
        this->x += x;
        this->y += y;
    }

    void UpdateChildren() {
        for(int i = 0; i < this->children.size(); i++){
            this->children[i]->childUpdate();
        }
        this->UpdateComponents();
    }

    void UpdateComponents() {
        Transformable* asTransformable;
        for(int i = 0; i < this->drawables.size(); i++) {
            asTransformable = dynamic_cast<Transformable*>(this->drawables[i]);
            asTransformable->setPosition(this->x, this->y);
        }

        this->collider->setPosition(this->x, this->y);
    }

    // Virtual
    virtual void OnStart() = 0; // NOT IMPLEMENTED
    virtual void OnUpdate() = 0;
};