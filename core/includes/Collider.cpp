#pragma once
#include <SFML/Graphics.hpp>
#include "Gameobject.cpp"

using namespace sf;

class Collider : public GameObject {
private:
  FloatRect area;

public:
  static vector<Collider*> all_colliders;

  static void ClearColliders() {
    Collider::all_colliders.clear();
    Collider::all_colliders.shrink_to_fit();
  }

  Collider(Vector2f size = Vector2f(1,1), bool debug_on = false, string id = "@collider@", float x = 0, float y = 0, float z = -2147483648) : GameObject(id, x, y, z) {
    this->area = FloatRect(this->x, this->y, size.x, size.y); 
    if (debug_on) {
      RectangleShape* shape = new RectangleShape(size);
      shape->setOutlineColor(Color::Red);
      shape->setOutlineThickness(1);
      shape->setFillColor(Color(255,255,255,0));
      this->PushDrawable(shape);
      Collider::all_colliders.push_back(this);
    }
  }

  // Contains & Intersects

  Collider* isColliding(string id = "", string tag = "") {
    if (id != "") { // Search by ID
      for (size_t i = 0; i < Collider::all_colliders.size(); i++) {
        if (Collider::all_colliders.at(i) == this) continue;

        if (Collider::all_colliders.at(i)->parent->id == id) {
          Collider* potential_collision = Collider::all_colliders.at(i);
          if (potential_collision->area.intersects(this->area))  {
            return potential_collision;
          }
        }
      }
    } else if (tag != "") { // Search By TAG
      for (size_t i = 0; i < Collider::all_colliders.size(); i++) {
        if (Collider::all_colliders.at(i) == this) continue;

        if (Collider::all_colliders.at(i)->parent->objectTag == tag) {
          Collider* potential_collision = Collider::all_colliders.at(i);
          if (potential_collision->area.intersects(this->area))  {
            return potential_collision;
          }
        }
      }
    }

    return nullptr;
  }

  // =====================

  void ChangeSize(Vector2f newSize) {
    this->area.height = newSize.y;
    this->area.width = newSize.x;
  }

  void Update() override {
    this->area.left = this->x;
    this->area.top = this->y;
  };
};

vector<Collider*> Collider::all_colliders = vector<Collider*>();