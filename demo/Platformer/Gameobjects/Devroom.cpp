#pragma once
#include "Player.cpp"
#include "/home/deb/Documents/git/Cookie/demo/Platformer/includes/Scene.hpp"
class Devroom{
public:
Scene* scene = new Scene("Devroom", 1280, 720);
Devroom() {
Player* dynamic_Player;
dynamic_Player = new Player(352, 160);
this->scene->InsertObject(dynamic_Player);
}
};