#include <iostream>

#include "includes/CookieEngine.cpp"
#include "includes/Scene.cpp"
#include "includes/drawables/SpriteRenderer.cpp"
#include "includes/drawables/Figure.cpp"

using namespace std;

class TemplateObject : public GameObject {
private:
  Animation* walkAnimation = new Animation("demo/WALK.png", Vector2i(96, 96), 8);
  SpriteRenderer* renderer = new SpriteRenderer(this->walkAnimation);
  float speed = 10;
  Vector2f scale = Vector2f(3, 3);
public:
  TemplateObject() : GameObject(0, 0) {
    addChild(this->renderer);
    this->renderer->setScale(scale);
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
    if (xDir != 0) this->renderer->setScale(Vector2f(scale.x * xDir, scale.y));
  }

  void afterUpdate() {
    if (KeyInput::OnKeyDown(Keyboard::B)) this->renderer->toggleFreeze();
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
