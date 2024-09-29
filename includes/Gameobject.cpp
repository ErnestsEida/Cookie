#pragma once
#include <iostream>
#include <vector>

#include "helpers/Generators.cpp"
#include "interfaces/IDrawable.cpp"

using namespace std;

const int defaultCoord = 0;
const string defaultTag = "";
const string defaultName = "object";

class GameObject
{
private:
  vector<GameObject *> children = vector<GameObject *>();
  vector<IDrawable> drawables = vector<IDrawable>();

  void processDrawables()
  {
    for (IDrawable drawable : drawables)
    {
      drawable.z = this->z;
      if (drawable.source != nullptr)
      {
        Transformable *transform = drawable.transformable();
        transform->setPosition(this->realCoords());
      }
    }
  }

protected:
  Vector2f realCoords()
  {
    Vector2f parentPos = Vector2f(0, 0);
    Vector2f myPos = Vector2f(this->x, this->y);

    if (this->parent != nullptr)
    {
      parentPos = this->parent->realCoords();
    }

    return Vector2f(myPos.x + parentPos.x, myPos.y + parentPos.y);
  }

public:
  GameObject *parent = nullptr;
  bool isVisible = true;
  string objectName;
  string tag;
  string id;
  float x;
  float y;
  int z;

  GameObject(int x = defaultCoord, int y = defaultCoord, int z = defaultCoord, string objectName = defaultName, string tag = defaultTag)
  {
    this->id = Generators::MakeUniqID("gameobject_");
    this->objectName = objectName;
    this->tag = tag;
    this->x = x;
    this->y = y;
    this->z = z;
  }

  virtual void addChild(GameObject *child) final
  {
    child->parent = this;
    this->children.push_back(child);
  }

  /* TODO: Manage removed gameobject memory freeing -?-> Thread where all deleted gameobjects are saved and removed async? */
  virtual void removeChild(GameObject *childToRemove) final
  {
    vector<GameObject *> moveChildrenVec;
    for (GameObject *child : children)
    {
      if (child->id == childToRemove->id)
        continue;
      moveChildrenVec.push_back(child);
    }

    this->children = moveChildrenVec;
  }

  virtual void processChildren(string regulator) final
  {
    if (children.empty())
      return;

    for (GameObject *child : children)
    {
      if (regulator == "before")
      {
        child->beforeUpdate();
      }
      else if (regulator == "on")
      {
        child->onUpdate();
      }
      else if (regulator == "after")
      {
        child->afterUpdate();
      }

      child->processChildren(regulator);
    }
  }

  virtual void addDrawable(Drawable *drawable) final
  {
    this->drawables.push_back(IDrawable(drawable, this->z));
  }

  virtual void gDrawables(vector<IDrawable> &result) final
  {
    if (!this->drawables.empty() && this->isVisible)
    {
      this->processDrawables();
      result.insert(result.end(), this->drawables.begin(), this->drawables.end());
    }

    if (this->children.empty())
      return;

    for (GameObject *child : this->children)
    {
      child->gDrawables(result);
    }
  }

  virtual void beforeUpdate() {};
  virtual void onUpdate() {};
  virtual void afterUpdate() {};
};