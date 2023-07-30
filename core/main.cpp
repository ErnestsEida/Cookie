#include <iostream>
#include "includes/CookieEngine.cpp"

using namespace std;

int main() {
  CookieCore *e = new CookieCore();
  e->CreateWindow();
  e->Start();
  return 0;
}