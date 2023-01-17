#pragma once
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "Alerts.cpp"
#include "Gametime.cpp"
#include "Scene.cpp"
#include "Input.cpp"
#include "SceneManager.cpp"
#include "Collider.cpp"

using namespace sf;
using namespace std;

class CookieEngine {
private:
    bool isDisplayReady = false;
    bool closeWindowFlag = false;

    RenderWindow* display;
    Scene* scene = nullptr;

    void CreateDisplay(unsigned int width, unsigned int height, string title, ContextSettings settings) {
        this->display = new RenderWindow(VideoMode(width, height), title, Style::Default, settings);
        this->isDisplayReady = true;
    }
public:
    static CookieEngine* singleton;

    CookieEngine() {
        if (CookieEngine::singleton == nullptr) {
            CookieEngine::singleton = this;
        } else {
            Alerts::Error("Trying to create another instance of CookieEngine, when there already an existing one!");
        }
    }

    // Display ===================================================

    void InitDisplay() {
        unsigned int width = VideoMode::getDesktopMode().width;
        unsigned int height = VideoMode::getDesktopMode().height;
        this->CreateDisplay(width, height, "Game Display", *new ContextSettings());
    }

    void InitDisplay(unsigned int width, unsigned int height, string title) {
        this->CreateDisplay(width, height, title, *new ContextSettings());
    }

    void InitDisplay(string title) {
        this->InitDisplay();
        this->display->setTitle(title);
    }

    // Miscelaneus ================================================

    // I think as of now CloseGame() and CloseWindow() both just end the mainloop, maybe should create top-level-loop for game and use inside loop for window
    // And should think of multiple window support?
    void CloseGame() {
        exit(0);
    }

    void CloseWindow() {
        this->closeWindowFlag = true;
    }

    // =============================================================

    // SCENE =======================================================

    void SetScene(string scene_name) {
        if (this->scene != nullptr) this->scene->ClearGameObjects();
        this->scene = SceneManager::GetScene(scene_name);
        this->scene->SetupScene();
    }

    void DestroyObject(GameObject* object) {
        this->scene->RemoveGameObject(object);
    }

    // =============================================================

    // =============================================================
    
    void Run() {
        if (!this->isDisplayReady) Alerts::Error("Can't start mainloop without initializing display!"); 

        // setup
        auto tp1 = chrono::system_clock::now();
        auto tp2 = chrono::system_clock::now();

        if (this->scene == nullptr) Alerts::Warning("Game was run without a scene!");

        vector<GameObject*> gameobjects;
        vector<IDrawable*> all_drawables;

        while(this->display->isOpen()) {
            if (this->closeWindowFlag) this->display->close();
            
            Input::UpdateKeyStates();

            // deltaTime update
            tp2 = chrono::system_clock::now();
            chrono::duration<float> elapsedTime = tp2 - tp1;
		    tp1 = tp2;
		    Gametime::deltaTime = elapsedTime.count();
            
            Event event;
            while(this->display->pollEvent(event)) {
                if (event.type == Event::Closed) this->display->close();
            }

            // Gameobjects and scene stuff
            if (scene != nullptr) {
                gameobjects = this->scene->GetGameObjects();
                // Update necessary data
                for(size_t i = 0; i < gameobjects.size(); i++) {
                    gameobjects.at(i)->Update();
                    gameobjects.at(i)->UpdateChildren();
                    gameobjects.at(i)->UpdateDrawables();
                }
                
                // Get drawables

                for(size_t i = 0; i < gameobjects.size(); i++) {
                    vector<IDrawable*> object_drawables = gameobjects.at(i)->GetDrawables();
                    all_drawables.insert(all_drawables.end(), object_drawables.begin(), object_drawables.end());
                }
                all_drawables = IDrawable::SortByZ(all_drawables);

                // Draw
                this->display->clear();

                for(size_t i = 0;i < all_drawables.size();i++){
                    if (all_drawables.at(i) != nullptr)
                        this->display->draw(*all_drawables.at(i)->drawable);
                }

                this->display->display();

                all_drawables.clear();
            }
        }
    }
    // =============================================================
};

CookieEngine* CookieEngine::singleton = nullptr;