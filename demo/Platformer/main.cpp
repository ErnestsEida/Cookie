#include "includes/Cookie.cpp"
#include "includes/Scene.hpp"
#include "Gameobjects/Devroom.cpp"

int main() {
    Cookie c;

    c.CreateWindow(1280, 720, "Platformer game");
    Devroom *room = new Devroom();
    c.LoadScene(room->scene);
    c.Run();
    return 0;
}