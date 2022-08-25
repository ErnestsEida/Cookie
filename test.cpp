#include "includes/Cookie.cpp"
#include "demo/Player.hpp"
#include "demo/Child.hpp"

int main(){
    Cookie c;
    c.CreateWindow(1280, 720, "Game1");
    Player x(50, 50);

    Child* f;
    for(int i = 0;i < 20;i++){
        f = new Child(50*i, 500);
        f->setZ(-1);
    }
    
    c.Run();
    return 0;
}