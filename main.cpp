#include <iostream>

#include "includes/CookieEngine.cpp"
#include "includes/Scene.cpp"
#include "includes/drawables/SpriteRenderer.cpp"

using namespace std;

class CustomRenderer : public SpriteRenderer {
public:
  CustomRenderer(Animation* a) : SpriteRenderer(a) {
    this->setScale(Vector2f(10, 10));
  }
};

class TemplateObject : public GameObject {
private:
  Animation* walkAnimation = new Animation("demo/WALK.png", Vector2i(96, 96), 8);
  float speed = 10;
public:
  TemplateObject() : GameObject(100, 100) {
    addChild(new CustomRenderer(walkAnimation));
  }

  void beforeUpdate() {
    if (KeyInput::OnKeyUp(Keyboard::Key::Escape)) CookieEngine::singleton->Stop();
    if (KeyInput::OnKeyDown(Keyboard::Key::N)) CookieEngine::singleton->sceneManager.changeScene("main2");
  }

  void onUpdate() {
    x += (KeyInput::OnKey(Keyboard::Key::D) - KeyInput::OnKey(Keyboard::Key::A)) * speed * CookieEngine::deltaTime;
    y += (KeyInput::OnKey(Keyboard::Key::S) - KeyInput::OnKey(Keyboard::Key::W)) * speed * CookieEngine::deltaTime;
  }

  void afterUpdate() {}
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
