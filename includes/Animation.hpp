#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Alerts.cpp"

using namespace std;
using namespace sf;

class Animation {
private:
    Texture spritesheet;
    Sprite* sprite = NULL;
    string spriteFilePath = "";
    Vector2i spriteSize;
    int frame_count;

    Clock clock;
public:
    Animation(string path, int width, int height, int frame_count) {
        this->spriteFilePath = path;
        this->spriteSize = Vector2i(width, height);
        this->frame_count = frame_count;
        this->setFirstFrame();
    }

    Sprite* getSprite() const {
        return this->sprite;
    }

    void setFirstFrame() {
        if (!this->spritesheet.loadFromFile(this->spriteFilePath, IntRect(Vector2i(0, 0), this->spriteSize))) {
            Alerts::ErrorMessage("Couldn't load \"" + this->spriteFilePath + "\"!");
            return ;
        }
        this->sprite = new Sprite(this->spritesheet, IntRect(Vector2i(32,32), this->spriteSize));
    }

    void NextSprite() {
        IntRect rect = this->sprite->getTextureRect();
        if (rect.left + this->spriteSize.x >= (this->frame_count * this->spriteSize.x)) {
            rect.left = 0;
        } else {
            rect.left += this->spriteSize.x;
        }
        cout << rect.left << endl;
        this->sprite->setTextureRect(rect);
    }

    void TryNextSprite() {
        if (this->sprite != NULL) {
            if (this->clock.getElapsedTime().asSeconds() > 1.0 / this->frame_count) {
                this->NextSprite();
                this->clock.restart();
            }
        }
    }
};