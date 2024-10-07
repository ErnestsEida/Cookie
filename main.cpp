#include <iostream>

#include "includes/CookieEngine.cpp"
#include "demo/MainScene.cpp"
#include "demo/Main2Scene.cpp"
#include "includes/audibles/AudioTrack.cpp"

using namespace std;

int main()
{
  AudioTrack::registerTrack("main");
  Scene::AddScene("main", new MainScene());
  Scene::AddScene("main2", new MainScene2());

  CookieEngine *engine = new CookieEngine();
  engine->Start();
  return 0;
}
