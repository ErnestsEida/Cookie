#include "../../includes/Cookie.cpp"
#include "../../includes/Scene.hpp"

int main() {
    Cookie c;

    c.CreateWindow(1280, 720, "Platformer game");

    c.Run();
    return 0;
}