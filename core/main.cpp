#include <iostream>
#include "includes/CookieEngine.cpp"
#include "demo/Template.cpp"

using namespace std;

int main() {
  GameRoom::AddRoom("x", new Template());
  GameRoom::AddRoom("y", new Template2());

  CookieCore *e = new CookieCore();

  e->CreateWindow(1280, 720);
  e->ChangeRoom("x");
  e->Start();
  
  return 0;
}