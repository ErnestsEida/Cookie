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
    GameObject::object_count++;
    InsertNewObject(this);
}

// GETTERS
int GameObject::GetX() const {
    return this->x;
}

int GameObject::GetY() const {
    return this->y;
}

int GameObject::GetZ() const {
    return this->z;
}

string GameObject::GetObjectName() const {
    return this->object_name;
}

string GameObject::GetTag() const {
    return this->tag;
}

vector<Transformable*> GameObject::GetDrawables() const {
    return this->drawable_components;
}

FloatRect* GameObject::Get_Collider() const {
    return this->collider;
}

Vector2f GameObject::Get_Origin() const {
    return this->origin;
}

// SETTERS
void GameObject::SetX(int x) {
    this->x = x;
}

void GameObject::SetY(int y) {
    this->y = y;
}

void GameObject::SetZ(int z) {
    this->z = z;
}

void GameObject::SetObjectName(string object_name) {
    this->object_name = object_name;
}

void GameObject::SetTag(string tag) {
    this->tag = tag;
}

void GameObject::SetCollider(float width, float height) {
    this->collider = new FloatRect(this->x, this->y, width, height);
}

void GameObject::SetComponent(Component* component) {
    this->components.push_back(component);
}

void GameObject::SetOrigin(float origin_x, float origin_y){
    this->origin = Vector2f(origin_x, origin_y);
    this->ApplyDrawableOrigin();
}

// MISCELANEOUS
void GameObject::InsertNewObject(GameObject* object) {
    GameObject::object_vector.push_back(object);
}

void GameObject::InsertDrawable(Transformable* drawable) {
    drawable->setPosition(this->x, this->y);
    this->drawable_components.push_back(drawable);
}

void GameObject::ClearDrawables() {
    this->drawable_components.clear();
}

// AUTO-CALL 

void GameObject::SyncComponents() {
    for(int i = 0; i < this->drawable_components.size();i++){
        this->drawable_components[i]->setPosition(this->x, this->y);
    }
    this->ApplyDrawableOrigin();
    float newX = this->x - this->origin.x;
    float newY = this->y - this->origin.y;
    this->UpdateCollider(newX, newY);
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

void GameObject::TriggerComponents() {
    this->ClearDrawables();
    for(int i = 0; i < this->components.size();i++){
        this->components[i]->Trigger();
        this->AppendDrawables(this->components[i]->GetDrawables());
    }
}

// PRIVATES
void GameObject::AppendDrawables(vector<Transformable*> drawables){
    if (drawables.size() < 1) { return; }
    this->drawable_components.insert(this->drawable_components.end(), drawables.begin(), drawables.end());
}

void GameObject::ApplyDrawableOrigin() {
    for(int i = 0;i < this->drawable_components.size(); i++){
        this->drawable_components[i]->setOrigin(this->origin);
    }
}

void GameObject::UpdateCollider(float left, float top) {
    this->collider->left = left;
    this->collider->top = top;
}