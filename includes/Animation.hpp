#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Animation {
private:
    Texture spritesheet;
    Sprite* sprite;
    Clock clock;
    int sprite_count, width, height;
public:
    Animation(string spritesheet_path, int single_width, int single_height, int sprite_count){
        this->spritesheet.loadFromFile(spritesheet_path);
        this->width = single_width;
        this->height = single_height;
        this->sprite_count = sprite_count;
        this->sprite = new Sprite(this->spritesheet, IntRect(0, 0, this->width, this->height));
    }

    Sprite* GetSprite() const {
        return this->sprite;
    }

    int GetSpriteCount() {
        return this->sprite_count;
    }

    void SetSpriteScale(Vector2f scale) {
        this->sprite->setScale(scale);
    }

    void NextSprite() {
        IntRect textureRect = this->sprite->getTextureRect();
        if (textureRect.left + this->width >= (this->sprite_count + this->width)){
            textureRect.left = 0;
        } else {
            textureRect.left += this->width;
        }
        this->sprite->setTextureRect(textureRect);
    }
};