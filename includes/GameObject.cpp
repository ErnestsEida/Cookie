#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "IDrawable.cpp"

using namespace std;
using namespace sf;

class GameObject {
private:
    // Defaults
    const int DEFAULT_COORD = 0;
    const string DEFAULT_TAG = "default";
    const string DEFAULT_OBJECT_NAME = "object" + to_string(GameObject::object_count);

    // Other
    bool isChild = false;

    vector<GameObject*> children;
    vector<IDrawable*> drawables;

    void SetupObject(float x, float y, int z, string objectName, string tag) {
        this->x = offset_x = x;
        this->y = offset_y = y;
        this->z = z;
        this->objectName = objectName;
        this->tag = tag;
        GameObject::object_count++;
    }

protected:
    void ClearDrawables() {
        this->drawables.clear();
    }

    GameObject* parent = nullptr;

public:
    float x, offset_x;
    float y, offset_y;
    int z;
    string objectName;
    string tag;
    bool isVisible = true;

    static int object_count;

    // CONSTRUCTORS ===========================================================
    GameObject() {
        this->SetupObject(DEFAULT_COORD, DEFAULT_COORD, DEFAULT_COORD, DEFAULT_OBJECT_NAME, DEFAULT_TAG);
    }

    GameObject(float x, float y) {
        this->SetupObject(x, y, DEFAULT_COORD, DEFAULT_OBJECT_NAME, DEFAULT_TAG);
    }

    GameObject(float x, float y, int z) {
        this->SetupObject(x, y, z, DEFAULT_OBJECT_NAME, DEFAULT_TAG);
    }

    GameObject(float x, float y, int z, string objectName) {
        this->SetupObject(x, y, z, objectName, DEFAULT_TAG);
    }

    GameObject(float x, float y, int z, string objectName, string tag){
        this->SetupObject(x, y, z, objectName, tag);
    }

    ~GameObject() {
        for(size_t i = 0; i < this->children.size(); i++) {
            delete this->children.at(i);
        }
        cout << this->objectName << ": Gameobject Delete" << endl;
    }
    // ==========================================================================

    // Drawables ========================================================
    
    void AddDrawable(IDrawable* drawable) {
        this->drawables.push_back(drawable);
    }

    vector<IDrawable*> GetDrawables() {
        vector<IDrawable*> resulting_drawables;
        if (this->children.size() != 0) {
            for(size_t i = 0; i < this->children.size(); i++) {
                GameObject* child = this->children.at(i);
                vector<IDrawable*> children_drawables = child->GetDrawables();
                resulting_drawables.insert(resulting_drawables.end(), children_drawables.begin(), children_drawables.end());
            }
        }

        resulting_drawables.insert(resulting_drawables.end(), this->drawables.begin(), this->drawables.end());

        return resulting_drawables;
    }

    void UpdateDrawables() {
        if (this->children.size() != 0) {
            for(size_t i = 0; i < this->children.size(); i++) {
                this->children.at(i)->UpdateDrawables();
            }
        }
        
        Transformable* asTransformable;
        for(size_t i = 0; i < this->drawables.size(); i++) {
            if (this->drawables.at(i) == nullptr) continue;
            this->drawables.at(i)->z = this->z;
            asTransformable = dynamic_cast<Transformable*>(this->drawables.at(i)->drawable);
            asTransformable->setPosition(this->x, this->y);
        }
    }
    
    // ==========================================================================

    // Children & Parent ========================================================

    void UpdateChildren() {
        if (this->children.size() == 0) return;
        for(size_t i = 0; i < this->children.size(); i++) {
            GameObject* child = this->children.at(i);
            child->Update();
            child->x = this->x + child->offset_x;
            child->y = this->y + child->offset_y;
            child->z = this->z;
            child->UpdateChildren();
        }
    }

    bool isParent() {
        return this->isChild == false;
    }

    void AddChild(GameObject* object) {
        object->isChild = true;
        object->parent = this;
        object->x = this->x + object->offset_x;
        object->y = this->y + object->offset_y;
        object->z = this->z;
        this->children.push_back(object);
    }

    // ==========================================================================

    // VIRTUAL FUNCTIONS ========================================================
    virtual void Update() = 0;
    // ==========================================================================
};

int GameObject::object_count = 0;