#include "gameobjects/Player.cpp"
#include "gameobjects/Block.cpp"
#include "gameobjects/Scene1.cpp"
#include "gameobjects/Scene2.cpp"

#include <iostream>

using namespace std;

void SetupScenes() {
    SceneManager::AddScene("room1", new Scene1());
    SceneManager::AddScene("room2", new Scene2());
}

int main() {
    SetupScenes();

    CookieEngine e;
    e.InitDisplay(1280, 720, "Game");
    e.SetScene("room1");
    e.Run();
    return 0;
}

// !!! On Scene change objects don't destroy correctly taking up memory with unused gameobjects

// Different pipeline for persistant gameobject ( objects that don't get destroyed on scene change )

// Create AudioPlayer

// Create Viewport/Camera