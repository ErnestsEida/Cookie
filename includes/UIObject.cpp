#include "UIObject.h"

vector<UIObject*> UIObject::objects;

UIObject::UIObject(int x, int y){
    this->x = x;
    this->y = y;
    UIObject::objects.push_back(this);
}

UIObject::UIObject(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
    UIObject::objects.push_back(this);
}

void UIObject::AddDrawable(Transformable* drawable) {
    drawable->setPosition(Vector2f(this->x, this->y));
    this->drawables.push_back(drawable);
}

void UIObject::SetCollider(int width, int height) {
    this->collider = new IntRect(this->x, this->y, width, height);
}

vector<Transformable*> UIObject::GetDrawables() const {
    return this->drawables;
}

void UIObject::Update() {
    if (this->collider != NULL){
        if (this->collider->contains(Mouse::getPosition())){
            if (this->mouse_inside){
                this->MouseOnHover();
            } else {
                this->MouseOnEnter();
            }
            this->mouse_inside = true;
        } else {
            if (this->mouse_inside) {
                this->MouseOnExit();
            }
            this->mouse_inside = false;
        }
    }
}