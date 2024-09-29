#pragma once

#include "../CookieEngine.cpp"
#include "../Profiler.cpp"

namespace WindowHelper {
  bool windowPresent() {
    if (CookieEngine::singleton == nullptr) {
      Profiler::Warning("[WindowHelper] Cannot use window helper without CookieEngine instance");
      return false;
    }

    return true;
  }

  Vector2u windowSize() {
    if (!windowPresent()) return Vector2u(0, 0); 
    return CookieEngine::singleton->windowManager.window->getSize();
  }
}