#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class C_RenderWindow {
private:
  uint desktopWidth() const { return VideoMode::getDesktopMode().width; }

  uint desktopHeight() const { return VideoMode::getDesktopMode().height; }  

  void Init() {
    this->window = new RenderWindow(VideoMode(this->desktopWidth(), this->desktopHeight()), "CookieEngine Render Window", Style::Default, ContextSettings());
  }

public:
  RenderWindow* window = nullptr;

  C_RenderWindow() {
    this->Init();
  }
};