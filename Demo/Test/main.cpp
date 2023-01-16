#include "gameobjects/Player.cpp"
#include "gameobjects/Block.cpp"
#include "gameobjects/Scene1.cpp"

#include <iostream>

using namespace std;

int main() {
    CookieEngine e;
    e.InitDisplay(1280, 720, "Game");
    e.SetScene(new Scene1());
    e.Run();
    return 0;
}

// Errors with memory allocation and freeing in the process of changing scenes!!