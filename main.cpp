#include <iostream>

#include "includes/CookieEngine.cpp"
#include "demo/MainScene.cpp"

using namespace std;

int main() {
  Scene::AddScene("main", new MainScene());

  CookieEngine* engine = new CookieEngine();
  engine->Start();
  return 0;
}
