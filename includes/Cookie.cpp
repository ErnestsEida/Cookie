#pragma once

// All SFML Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// STD Includes
#include <iostream>

// Engine
#include "Alerts.cpp"
#include "GameObject.cpp"

using namespace sf;
using namespace std;

class Cookie {
private:
    // ATTRIBUTES
    bool closeWindowFlag = false;
    bool windowInitializationFlag = false;
    RenderWindow* window;
public:
    // GETTERS
    RenderWindow* getWindow() const {
        return this->windowInitializationFlag ? this->window : nullptr;
    }

    // SETTERS
    void setWindow(RenderWindow* window) {
        this->window = window;
    }

    // MISC
    void CreateWindow(unsigned int width,unsigned int height, string title) {
        this->window = new RenderWindow(VideoMode(width, height), title, Style::Default);
        this->windowInitializationFlag = true;
    }

    void CreateWindow(unsigned int width,unsigned int height, string title, ContextSettings settings) {
        this->window = new RenderWindow(VideoMode(width, height), title, Style::Default, settings);
        this->windowInitializationFlag = true;
    }

    void CloseWindow() {
        this->closeWindowFlag = true;
    }

    void Run() {
        if (!this->windowInitializationFlag) {
            Alerts::ErrorMessage("window has not been initialized!");
            return ;
        }

        vector<GameObject*> all_gameobjects;
        vector<GameObject*> parent_gameobjects;
        vector<Drawable*> all_drawables;
        while(this->window->isOpen()){
            if (this->closeWindowFlag) this->window->close();
            
            Event event;
            while(this->window->pollEvent(event)){
                if (event.type == Event::Closed) this->window->close();
            }

            GameObject::SortObjectsByZ();
            all_gameobjects = GameObject::getAllObjects();
            parent_gameobjects = GameObject::getParentObjects();

            // UPDATE ALL GAMEOBJECTS AND UPLOAD DRAWABLES
            for(int i = 0; i < all_gameobjects.size(); i++){
                all_gameobjects[i]->OnUpdate();
                all_gameobjects[i]->UpdateComponents();
                vector<Drawable*> object_drawables = all_gameobjects[i]->getDrawables();
                all_drawables.insert(all_drawables.end(), object_drawables.begin(), object_drawables.end());
            }

            // SYNC CHILDREN WITH THEIR PARENTS
            for(int i = 0;i < parent_gameobjects.size();i++){
                parent_gameobjects[i]->UpdateChildren();
            }

            this->window->clear();

            for(int i = 0;i < all_drawables.size();i++){
                this->window->draw(*all_drawables[i]);
            }

            this->window->display();
        }
    }
};