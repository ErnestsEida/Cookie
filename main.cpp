#include <iostream>

#include "includes/CookieEngine.cpp"
#include "includes/Scene.cpp"

using namespace std;

class TemplateObject : public GameObject {
  void beforeUpdate() {}

  void onUpdate() {
    if (KeyInput::OnKeyDown(Keyboard::Key::N)) CookieEngine::singleton->sceneManager.changeScene("main2");
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
