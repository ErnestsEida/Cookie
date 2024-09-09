#include <iostream>

#include "includes/CookieEngine.cpp"

using namespace std;

void ass(int& x) {
  x = 20;
}

int main() {
  CookieEngine engine;
  engine.Start();
  return 0;
}
