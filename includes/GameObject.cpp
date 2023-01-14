#pragma once
#include <iostream>
#include <vector>

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
    vector<Drawable*> drawables;

    void SetupObject(float x, float y, int z, string objectName, string tag) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->objectName = objectName;
        this->tag = tag;
        GameObject::object_count++;
    }

protected:
    void ClearDrawables() {
        this->drawables.clear();
    }

public:
    float x;
    float y;
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
    // ==========================================================================

    // Drawables ========================================================
    
    void AddDrawable(Drawable* drawable) {
        this->drawables.push_back(drawable);
    }

    vector<Drawable*> GetDrawables() {
        vector<Drawable*> resulting_drawables;
        if (this->children.size() != 0) {
            for(size_t i = 0; i < this->children.size(); i++) {
                GameObject* child = this->children.at(i);
                vector<Drawable*> children_drawables = child->GetDrawables();
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
        cout << this->x << endl;
        for(size_t i = 0; i < this->drawables.size(); i++) {
            if (this->drawables.at(i) == nullptr) continue;
            asTransformable = (Transformable*) this->drawables.at(i);
            asTransformable->setPosition(this->x, this->y);
        }
    }
    
    // ==========================================================================

    // Children & Parent ========================================================

    void PreUpdateChildren() {
        if (this->children.size() == 0) return;
        for(size_t i = 0; i < this->children.size(); i++) {
            this->children.at(i)->x -= this->x;
            this->children.at(i)->y -= this->y;
        }
    }

    void UpdateChildren() {
        if (this->children.size() == 0) return;
        for(size_t i = 0; i < this->children.size(); i++) {
            this->children.at(i)->Update();
            this->children.at(i)->x += this->x;
            this->children.at(i)->y += this->y;
        }
    }

    bool isParent() {
        return this->isChild == false;
    }

    void AddChild(GameObject* object) {
        object->isChild = true;
        this->children.push_back(object);
    }

    // ==========================================================================

    // VIRTUAL FUNCTIONS ========================================================
    virtual void Update() = 0;
    // ==========================================================================
};

int GameObject::object_count = 0;