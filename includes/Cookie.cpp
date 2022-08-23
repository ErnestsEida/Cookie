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

        while(this->window->isOpen()){
            if (this->closeWindowFlag) this->window->close();
            
            Event event;
            while(this->window->pollEvent(event)){
                if (event.type == Event::Closed) this->window->close();
            }

            this->window->clear();
            this->window->display();
        }
    }
};