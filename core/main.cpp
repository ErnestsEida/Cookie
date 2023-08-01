#include <iostream>
#include "includes/CookieEngine.cpp"
#include "demo/rooms.cpp"

using namespace std;

int main() {
  GameRoom::AddRoom("x", new Room1);
  CookieCore *e = new CookieCore();

  e->CreateWindow(1280, 720);
  e->ChangeRoom("x");
  e->Start();
  
  return 0;
}