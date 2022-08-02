#include "./GameObject.h"

using namespace std;
using namespace sf;

const int DEFAULT_COORD          = 0;
const string DEFAULT_TAG         = "none";
const string DEFAULT_OBJECT_NAME = "object";

int GameObject::object_count = 0;
vector<GameObject*> GameObject::object_vector;

// CONSTRUCTORS
GameObject::GameObject() {
    this->x = DEFAULT_COORD;
    this->y = DEFAULT_COORD;
    this->z = DEFAULT_COORD;
    this->object_name = DEFAULT_OBJECT_NAME + to_string(GameObject::object_count);
    this->tag = DEFAULT_TAG;
    this->collider = new FloatRect(this->x, this->y, 1, 1);
    this->sprite_renderer = new SpriteRenderer();
    GameObject::object_count++;
    InsertNewObject(this);
}

GameObject::GameObject(int x, int y) {
    this->x = x;
    this->y = y;
    this->z = DEFAULT_COORD;
    this->object_name = DEFAULT_OBJECT_NAME + to_string(GameObject::object_count);
    this->tag = DEFAULT_TAG;
    this->collider = new FloatRect(this->x, this->y, 1, 1);
    this->sprite_renderer = new SpriteRenderer();
    GameObject::object_count++;
    InsertNewObject(this);
}

GameObject::GameObject(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->object_name = DEFAULT_OBJECT_NAME + to_string(GameObject::object_count);
    this->tag = DEFAULT_TAG;
    this->collider = new FloatRect(this->x, this->y, 1, 1);
    this->sprite_renderer = new SpriteRenderer();
    GameObject::object_count++;
    InsertNewObject(this);
}

GameObject::GameObject(int x, int y, int z, string object_name) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->object_name = object_name;
    this->tag = DEFAULT_TAG;
    this->collider = new FloatRect(this->x, this->y, 1, 1);
    this->sprite_renderer = new SpriteRenderer();
    GameObject::object_count++;
    InsertNewObject(this);
}

GameObject::GameObject(int x, int y, int z, string object_name, string tag) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->object_name = object_name;
    this->tag = tag;
    this->collider = new FloatRect(this->x, this->y, 1, 1);
    this->sprite_renderer = new SpriteRenderer();
    GameObject::object_count++;
    InsertNewObject(this);
}

// GETTERS
int GameObject::Get_X() const {
    return this->x;
}

int GameObject::Get_Y() const {
    return this->y;
}

int GameObject::Get_Z() const {
    return this->z;
}

string GameObject::Get_ObjectName() const {
    return this->object_name;
}

string GameObject::Get_Tag() const {
    return this->tag;
}

vector<Transformable*> GameObject::GetDrawables() const {
    return this->drawable_components;
}

FloatRect* GameObject::Get_Collider() const {
    return this->collider;
}

// SETTERS
void GameObject::Set_X(int x) {
    this->x = x;
}

void GameObject::Set_Y(int y) {
    this->y = y;
}

void GameObject::Set_Z(int z) {
    this->z = z;
}

void GameObject::Set_ObjectName(string object_name) {
    this->object_name = object_name;
}

void GameObject::Set_Tag(string tag) {
    this->tag = tag;
}

void GameObject::Set_Collider(float width, float height) {
    this->collider = new FloatRect(this->x, this->y, width, height);
}

void GameObject::Set_Animation(Animation* animation) {
    this->sprite_renderer->SetAnimation(animation);
    this->drawable_components.clear();
    this->InsertDrawable(this->sprite_renderer->GetSprite());
}

// MISCELANEOUS
void GameObject::InsertNewObject(GameObject* object) {
    GameObject::object_vector.push_back(object);
}

void GameObject::InsertDrawable(Transformable* drawable) {
    drawable->setPosition(this->x, this->y);
    this->drawable_components.push_back(drawable);
}

void GameObject::AddShape(GameShape shape){
    this->InsertDrawable(shape.GetAsTransformable());
}

// AUTO-CALL 

void GameObject::SyncComponents() {
    for(int i = 0; i < this->drawable_components.size();i++){
        this->drawable_components[i]->setPosition(this->x, this->y);
    }
    this->collider = new FloatRect(this->x, this->y, this->collider->width, this->collider->height);
}

void GameObject::FindCollision() {
    GameObject* collision_object = NULL;
    for(int i = 0;i < this->object_vector.size();i++){
        if (this->object_vector[i] != this){
            if (this->collider->intersects(*this->object_vector[i]->collider)){
                collision_object = this->object_vector[i];
            }
        }
    }
    this->OnCollision(collision_object);
}

void GameObject::UpdateRenderer() {
    this->sprite_renderer->Iterate();
}