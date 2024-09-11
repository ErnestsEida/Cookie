#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../interfaces/IDrawable.cpp"

using namespace std;
using namespace sf;

class RenderWindowManager {
private:
  void isWindowPresent() const {
    if (this->window == nullptr || !this->window->isOpen()) {
      Profiler::Error("FATAL(RenderWindow): Trying to run manipulations on non-existing renderwindow");
    }
  }

  uint desktopWidth() const { return VideoMode::getDesktopMode().width; }

  uint desktopHeight() const { return VideoMode::getDesktopMode().height; }

  RenderWindow* defaultWindow() const {
    return new RenderWindow(VideoMode(this->desktopWidth(), this->desktopHeight()), "CookieEngine Render Window", Style::Default, ContextSettings());
  }

  void Init() {
    this->window = defaultWindow();
  }

public:
  RenderWindow* window = nullptr;

  RenderWindowManager() {
    this->Init();
  }

  void performDraw(vector<IDrawable> drawables) {
    isWindowPresent();
    this->window->clear();
    
    if (!drawables.empty()) {
      IDrawable::Sort(drawables);
      for(IDrawable drawable : drawables) {
        this->window->draw(*drawable.source);
      }
    }

    this->window->display();
  }
};