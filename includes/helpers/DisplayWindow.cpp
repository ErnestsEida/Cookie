#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "../interfaces/IDrawable.cpp"
#include "../Profiler.cpp"

using namespace std;
using namespace sf;

typedef pair<string, View> ViewPair;

class ViewManager
{
public:
  /* mainView is created on object construction and should be set to the RenderWindow as main */
  map<string, View> viewports;

  ViewManager() {} /* Ignore */

  ViewManager(View mainView)
  {
    this->viewports["main"] = mainView;
  }

  void addView(string key, View view)
  {
    this->viewports[key] = view;
  }

  void removeView(string key)
  {
    int erasedCount = this->viewports.erase(key);

    if (erasedCount == 0)
    {
      Profiler::Warning("[RenderWindow]: Cannot find view '" + key + "' to remove");
    }
  }

  View getView(string key)
  {
    try
    {
      View selected = this->viewports.at(key);
      return selected;
    }
    catch (out_of_range const &t)
    {
      Profiler::Warning("[RenderWindow]: Trying to fetch view '" + key + "' that doesn't exits");
      return View();
    }
  }
};

class DisplayWindow : public RenderWindow
{
private:
  ViewManager viewManager;

  void isWindowPresent() const
  {
    if (this->viewManager.viewports.empty())
    {
      Profiler::Error("FATAL(RenderWindow): No active views detected, at least 1 view should be present");
    }
  }

  uint desktopWidth() const { return VideoMode::getDesktopMode().width; }

  uint desktopHeight() const { return VideoMode::getDesktopMode().height; }

  void Init()
  {
    this->viewManager = ViewManager(this->getView());
  }

public:
  DisplayWindow(uint width = VideoMode::getDesktopMode().width, uint height = VideoMode::getDesktopMode().height, string title = "CookieGame", int style = Style::Default, ContextSettings settings = ContextSettings())
      : RenderWindow(VideoMode(width, height), title, style, settings)
  {
    this->Init();
  }

  void draw(vector<IDrawable> drawables)
  {
    isWindowPresent();
    this->clear();

    if (!drawables.empty())
    {
      IDrawable::Sort(drawables);
      for (ViewPair viewPair : this->viewManager.viewports)
      {
        this->setView(viewPair.second);
        for (IDrawable drawable : drawables)
        {
          if (drawable.source == nullptr)
            continue;
          RenderWindow::draw(*drawable.source);
        }
      }
    }

    this->display();
  }

  View fetchView(string key)
  {
    return this->viewManager.getView(key);
  }

  void addView(string key, View view)
  {
    this->viewManager.addView(key, view);
  }

  void removeView(string key)
  {
    this->viewManager.removeView(key);
  }
};