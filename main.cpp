#include <iostream>

#include "includes/CookieEngine.cpp"
#include "demo/MainScene.cpp"

using namespace std;

void defineScenes() {
  Scene::AddScene("main", new MainScene);
}

int main() {
  defineScenes();

  CookieEngine engine;
  engine.Start();
  return 0;
}
