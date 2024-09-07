#pragma once
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Profiler.cpp"
#include "helpers/C_RenderWindow.cpp"

using namespace std;
using namespace sf;

class CookieEngine {
private:
  bool closeWindowFlag = false;

public:
  static float deltaTime;
  static CookieEngine* singleton;

  C_RenderWindow renderWindow = C_RenderWindow();

  CookieEngine() {
    if (singleton == nullptr) {

      singleton = this; 
    }
    else Profiler::Error("FATAL: Cannot create two instances of CookieEngine at a time");
  }

  void Start() {
    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();
  
    while (this->renderWindow.window->isOpen()) {
      if (this->closeWindowFlag) this->renderWindow.window->close();
    
      // Calculate deltaTime
      tp2 = chrono::system_clock::now();
      chrono::duration<float> elapsedTime = tp2 - tp1;
      tp1 = tp2;
      deltaTime = elapsedTime.count();

      // SFML Events
      Event event;
      while(this->renderWindow.window->pollEvent(event)) {
        if (event.type == Event::Closed) this->renderWindow.window->close();
      }

      this->renderWindow.window->clear();
      this->renderWindow.window->display();
    }
  }
};

float CookieEngine::deltaTime = 0;
CookieEngine* CookieEngine::singleton = nullptr;