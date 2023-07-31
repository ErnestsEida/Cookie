#include <iostream>
#include "includes/CookieEngine.cpp"
#include "demo/Template.cpp"

using namespace std;

int main() {
  GameRoom::AddRoom("x", new Template());
  CookieCore *e = new CookieCore();

  e->CreateWindow();
  e->ChangeRoom("x");
  e->Start();
  
  return 0;
}