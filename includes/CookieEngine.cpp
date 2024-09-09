#pragma once
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Profiler.cpp"
#include "helpers/RenderWindowManager.cpp"
#include "helpers/SceneManager.cpp"
#include "KeyInput.cpp"

using namespace std;
using namespace sf;

class CookieEngine {
private:
  bool closeWindow = false;

  void validateTick() { /* TODO*/ }

  void setDeltaTime(chrono::_V2::system_clock::time_point& tp1, chrono::_V2::system_clock::time_point& tp2) {
    tp2 = chrono::system_clock::now();
    chrono::duration<float> elapsedTime = tp2 - tp1;
    tp1 = tp2;
    deltaTime = elapsedTime.count();
  }

public:
  RenderWindowManager windowManager = RenderWindowManager();
  
  static float deltaTime;
  static CookieEngine* singleton;

  CookieEngine() {
    if (singleton == nullptr) {

      singleton = this; 
    }
    else Profiler::Error("FATAL: Cannot create two instances of CookieEngine at a time");
  }

  void RunOnCloseCallbacks() { /* TODO */} 

  void Stop() {
    this->closeWindow = true;
  }

  void Start() {
    // Setup variables
    Event event;
    chrono::_V2::system_clock::time_point tp1 = chrono::system_clock::now();
    chrono::_V2::system_clock::time_point tp2 = chrono::system_clock::now();

    while(windowManager.window->isOpen()) {
      /* Close on exit and on closeWindow = true */
      while(windowManager.window->pollEvent(event)) {
        if (event.type == Event::Closed) { 
          closeWindow = true;
          break;
        }
      }
      if (closeWindow) { 
        RunOnCloseCallbacks();
        windowManager.window->close(); 
        break;
      }
      /* ============================== */

      validateTick();
      setDeltaTime(tp1, tp2);
      KeyInput::UpdateKeyStates();

      // Perform Updates
      // Run collision callbacks
      // Gather drawables

      windowManager.performDraw();
    }
  }
};

float CookieEngine::deltaTime = 0;
CookieEngine* CookieEngine::singleton = nullptr;