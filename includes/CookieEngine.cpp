#pragma once
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Profiler.cpp"
#include "helpers/RenderWindowManager.cpp"
#include "helpers/SceneManager.cpp"
#include "Gameobject.cpp"
#include "Collider.cpp"
#include "KeyInput.cpp"

using namespace std;
using namespace sf;

class CookieEngine
{
private:
  bool closeWindow = false;

  void validateTick() { /* TODO*/ }

  void RunOnCloseCallbacks() { /* TODO */ }

  bool isScenePopulated()
  {
    return !sceneManager.currentScene->objects.empty();
  }

  void setDeltaTime(chrono::_V2::system_clock::time_point &tp1, chrono::_V2::system_clock::time_point &tp2)
  {
    tp2 = chrono::system_clock::now();
    chrono::duration<float> elapsedTime = tp2 - tp1;
    tp1 = tp2;
    deltaTime = elapsedTime.count() * 60; // Multiply by 60 so its usable
  }

public:
  RenderWindowManager windowManager = RenderWindowManager();
  SceneManager sceneManager = SceneManager();

  static float deltaTime;
  static CookieEngine *singleton;

  CookieEngine()
  {
    if (singleton == nullptr)
    {
      singleton = this;
    }
    else
      Profiler::Error("FATAL: Cannot create two instances of CookieEngine at a time");
  }

  void Stop()
  {
    this->closeWindow = true;
  }

  void Start()
  {
    // Setup variables
    vector<IDrawable> sceneDrawables = vector<IDrawable>();
    Event event;
    chrono::_V2::system_clock::time_point tp1 = chrono::system_clock::now();
    chrono::_V2::system_clock::time_point tp2 = chrono::system_clock::now();

    while (windowManager.window->isOpen())
    {
      /* Close on exit and on closeWindow = true */
      while (windowManager.window->pollEvent(event))
      {
        if (event.type == Event::Closed)
        {
          closeWindow = true;
          break;
        }
      }
      if (closeWindow)
      {
        RunOnCloseCallbacks();
        windowManager.window->close();
        break;
      }
      /* ============================== */

      validateTick();
      setDeltaTime(tp1, tp2);
      KeyInput::UpdateKeyStates();

      sceneDrawables.clear();
      sceneDrawables.shrink_to_fit();
      Collider::reloadColliders();

      if (isScenePopulated())
      {
        for (GameObject *gameobject : sceneManager.currentScene->objects)
        {
          gameobject->beforeUpdate();
          gameobject->processChildren("before");

          gameobject->onUpdate();
          gameobject->processChildren("on");

          gameobject->afterUpdate();
          gameobject->processChildren("after");

          gameobject->gDrawables(sceneDrawables);
        }
      }

      windowManager.performDraw(sceneDrawables);
    }
  }
};

float CookieEngine::deltaTime = 0;
CookieEngine *CookieEngine::singleton = nullptr;