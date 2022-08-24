#include "includes/Cookie.cpp"
#include "demo/Player.hpp"
#include "demo/Child.hpp"

int main(){
    Cookie c;
    c.CreateWindow(1280, 720, "Game1");
    Player x(50, 50);
    c.Run();
    return 0;
}