#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include "Gameobject.cpp"

using namespace std;

typedef pair<string, bool> CollisionMap;

class Collider : public GameObject {
private:
  FloatRect area;
  RectangleShape* outline;
  map<string, bool> collisionStates;

  void BuildOutline(Vector2f size) {
    this->outline = new RectangleShape(size);
    this->outline->setFillColor(Color::Transparent);
    this->outline->setOutlineColor(Color::Red);
    this->outline->setOutlineThickness(2);
  }

  void BuildArea(Vector2f size) {
    this->area = FloatRect(this->realCoords(), size);
  }

  void setCalculatedOffset(Vector2f offset) {
    Vector2f correctedOffset = offset;
    correctedOffset.x -= this->area.width / 2;
    correctedOffset.y -= this->area.height / 2;
    this->x = correctedOffset.x;
    this->y = correctedOffset.y;
  }

  bool fetchCollisionState(string id) {
    map<string, bool>::iterator location = this->collisionStates.find(id);
    if (location == this->collisionStates.end()) {
      this->collisionStates[id] = false;
      return false;
    } else {
      return this->collisionStates[id];
    }
  }

  void performStateChange(Collider* target) {
    bool currentCollisionState = this->fetchCollisionState(target->id);
    
    try {
      if (target->area.intersects(this->area) && !currentCollisionState) {
        this->collisionStates[target->id] = true;
        this->enterCollision(target);
      } else if (!target->area.intersects(this->area) && currentCollisionState) {
        this->collisionStates[target->id] = false;
        this->exitCollision(target);
      } else if (currentCollisionState) {
        this->whileColliding(target);
      }
    } catch (bad_function_call const& e) {
      Profiler::Warning("[COLLIDER] Cannot call method for object " + this->id);
    }
  }
public:
  function<void(Collider*)> enterCollision = [](Collider* c){};
  function<void(Collider*)> whileColliding = [](Collider* c){};
  function<void(Collider*)> exitCollision = [](Collider* c){};

  static vector<Collider*> activeColliders;

  static void reloadColliders() {
    if (activeColliders.empty()) return;
    
    vector<Collider*> result;
    for(Collider* col : activeColliders) {
      if (col == nullptr) continue;
      result.push_back(col);
    }

    Collider::activeColliders = result;
  }

  Collider(Vector2f size, Vector2f offset = Vector2f(0, 0), string tag = "default") : GameObject(offset.x, offset.y) {
    this->isVisible = false;
    this->BuildArea(size);
    this->BuildOutline(size);
    this->setCalculatedOffset(offset);
    this->addDrawable(this->outline);
    Collider::activeColliders.push_back(this);
  }

  void setOutline(bool isVisible) {
    this->isVisible = isVisible;
  }

  virtual void beforeUpdate() final {
    Vector2f coords = this->realCoords();
    this->area.top = coords.x;
    this->area.left = coords.y;
  }

  virtual void onUpdate() final {
    for(Collider* col : Collider::activeColliders) {
      if (col->id == this->id) continue;
      this->performStateChange(col);
    }
  }

  virtual void afterUpdate() final {
    /* no functionality here */
  }
};

vector<Collider*> Collider::activeColliders = vector<Collider*>();
