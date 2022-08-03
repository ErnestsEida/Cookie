#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "SpriteRenderer.hpp"
#include "GameShape.hpp"

using namespace std;
using namespace sf;

class GameObject {
private:
    int x, y, z;
    string object_name;
    string tag;
    vector<Component*> components;
    vector<Transformable*> drawable_components;
    sf::FloatRect* collider;
    void AppendDrawables(vector<Transformable*>);
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
    int Get_X() const;
    int Get_Y() const;
    int Get_Z() const;
    string Get_ObjectName() const;
    string Get_Tag() const;
    vector<Transformable*> GetDrawables() const;
    FloatRect* Get_Collider() const;

    // SETTERS
    void Set_X(int);
    void Set_Y(int);
    void Set_Z(int);
    void Set_ObjectName(string);
    void Set_Tag(string);
    void Set_Collider(float, float);
    void Set_Component(Component*);

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