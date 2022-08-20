#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Component.hpp"

using namespace std;
using namespace sf;

class GameObject {
private:
    int x, y, z;
    string object_name;
    string tag;
    vector<Component*> components;
    vector<Transformable*> drawable_components;
    sf::FloatRect* collider = NULL;
    Vector2f origin = Vector2f(0, 0);

    void AppendDrawables(vector<Transformable*>);
    void ApplyDrawableOrigin();
    void UpdateCollider(float, float);
public:
    // STATIC VARIABLES
    static int object_count;
    static vector<GameObject*> object_vector;

    // Constructors
    GameObject();
    GameObject(int x, int y);
    GameObject(int x, int y, int z);
    GameObject(int x, int y, int z, string object_name);
    GameObject(int x, int y, int z, string object_name, string tag);

    // GETTERS
    int GetX() const;
    int GetY() const;
    int GetZ() const;
    string GetObjectName() const;
    string GetTag() const;
    vector<Transformable*> GetDrawables() const;
    FloatRect* Get_Collider() const;
    Vector2f Get_Origin() const;

    // SETTERS
    void SetX(int);
    void SetY(int);
    void SetZ(int);
    void SetObjectName(string);
    void SetTag(string);
    void SetCollider(float, float);
    void SetComponent(Component*);
    void SetOrigin(float, float);

    // MISCELANEOUS
    void InsertNewObject(GameObject*);
    void InsertDrawable(Transformable*); 
    void ClearDrawables();

    // AUTO-CALL METHODS
    void SyncComponents();
    void FindCollision();
    void TriggerComponents();

    // STEP FUNCTIONS
    virtual void Update() = 0;
    virtual void OnCollision(GameObject* other) = 0;
};