#include <iostream>

#include "includes/CookieEngine.cpp"

using namespace std;

int main() {
  CookieEngine* engine = new CookieEngine();
  engine->Start();
  return 0;
}
