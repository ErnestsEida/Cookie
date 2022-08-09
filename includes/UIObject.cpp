#include "UIObject.h"

vector<UIObject*> UIObject::objects;

UIObject::UIObject(int x, int y){
    this->constant_x = x;
    this->constant_y = y;
    UIObject::objects.push_back(this);
}

UIObject::UIObject(int x, int y, int z){
    this->constant_x = x;
    this->constant_y = y;
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

void UIObject::SyncDrawables(int relative_x, int relative_y) {
    this->x = relative_x + this->constant_x;
    this->y = relative_y + this->constant_y;
    this->collider->left = this->x;
    this->collider->top = this->y;
    for(int i = 0; i < this->drawables.size();i++){
        this->drawables[i]->setPosition(this->x, this->y);
    }
}

void UIObject::Update(RenderWindow *window) {
    View windowView = window->getView();
    int relative_x = windowView.getCenter().x - windowView.getSize().x / 2;
    int relative_y = windowView.getCenter().y - windowView.getSize().y / 2;
    // cout << "X:" << relative_x << ", " << "Y:" << relative_y << endl;
    this->SyncDrawables(relative_x, relative_y);

    if (this->collider != NULL){
        if (this->collider->contains((Vector2i) window->mapPixelToCoords(Mouse::getPosition()))){
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