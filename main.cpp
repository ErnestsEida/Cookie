#include <iostream>

#include "includes/CookieEngine.cpp"
#include "includes/Scene.cpp"
#include "includes/drawables/SpriteRenderer.cpp"
#include "includes/drawables/Figure.cpp"
#include "includes/Collider.cpp"

using namespace std;

class ChildObject : public GameObject {
};

class TemplateObject : public GameObject {
private:
  float speed = 10;
  Figure* fig = new Figure(Vector2f(50, 100), ShapeType::Rectangle); 
  Collider* collider = new Collider(Vector2f(50, 100));
public:
  TemplateObject() : GameObject(100, 100) {
    this->addChild(this->fig);
    this->addChild(this->collider);
  }

  void beforeUpdate() {
    if (KeyInput::OnKeyUp(Keyboard::Key::Escape)) CookieEngine::singleton->Stop();
    if (KeyInput::OnKeyDown(Keyboard::Key::N)) CookieEngine::singleton->sceneManager.changeScene("main2");
  }

  void onUpdate() {
    int xDir = (KeyInput::OnKey(Keyboard::Key::D) - KeyInput::OnKey(Keyboard::Key::A));
    int yDir = (KeyInput::OnKey(Keyboard::Key::S) - KeyInput::OnKey(Keyboard::Key::W));
    x += xDir * speed * CookieEngine::deltaTime;
    y += yDir * speed * CookieEngine::deltaTime;
  }
};

class TemplateScene : public Scene {
public:
  vector<GameObject*> GenerateObjects() {
    vector<GameObject*> r;
    r.push_back(new TemplateObject);
    return r;
  }
};

class TemplateScene2 : public Scene {
public:
  vector<GameObject*> GenerateObjects() {
    vector<GameObject*> r;
    return r;
  }
};

int main() {
  Scene::AddScene("main", new TemplateScene);
  Scene::AddScene("main2", new TemplateScene2);
  CookieEngine engine;
  engine.Start();
  return 0;
}
