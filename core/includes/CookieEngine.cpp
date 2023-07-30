#pragma once
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Alerts.cpp"
#include "Gametime.cpp"

using namespace sf;
using namespace std;

class CookieCore {
private:
  RenderWindow* window = nullptr;
  bool closeWindowFlag = false;

public:
  static CookieCore *singleton;

  CookieCore() {
    if (CookieCore::singleton == nullptr) {
      CookieCore::singleton = this;
    } else {
      Alerts::Error("Can't make another instance of CookieCore, when there is already one present!");
    }
  }

  // WINDOW MANAGEMENT

  void CreateWindow(unsigned int width = 0, unsigned int height = 0, string title = "CookieEngine Window", ContextSettings settings = ContextSettings()) {
    if (width == 0) {
      width = VideoMode::getDesktopMode().width;
    }

    if (height == 0) {
      height = VideoMode::getDesktopMode().height;
    }

    this->window = new RenderWindow(VideoMode(width, height), title, Style::Default, settings);
  }

  void CloseWindow() {
    this->closeWindowFlag = true;
  };

  // STARTING THE ENGINE

  void Start() {
    if (this->window == nullptr) Alerts::Error("Trying to start the engine without creating a window!");

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();

    while(this->window->isOpen()) {
      if (this->closeWindowFlag) this->window->close();

      // Calculate deltaTime
      tp2 = chrono::system_clock::now();
      chrono::duration<float> elapsedTime = tp2 - tp1;
      tp1 = tp2;
      Gametime::deltaTime = elapsedTime.count();
      // ==================

      Event event;
      while(this->window->pollEvent(event)) {
        if (event.type == Event::Closed) this->window->close();
      }
    }
    
  }
};

CookieCore* CookieCore::singleton = nullptr;