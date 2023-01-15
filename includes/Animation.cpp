#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Alerts.cpp"

using namespace std;
using namespace sf;

class Animation {
private:
    Clock timer;
    float animation_speed;
    int frame_count;
    Vector2i frame_size;
    Sprite* sprite = nullptr;
    bool loop = true;
    Texture texture;

    bool freezeFrame = false;
public:
    int current_frame = 0;

    Animation(string path_to_spritesheet, Vector2i frame_size, int frame_count, bool loop) {
        this->frame_count = frame_count;
        this->frame_size = frame_size;
        this->animation_speed = frame_count;
        this->loop = loop;

        this->texture = Texture();
        if (!this->texture.loadFromFile(path_to_spritesheet)) Alerts::Error("Couldn't find a spritesheet at: " + path_to_spritesheet);

        this->sprite = new Sprite(this->texture, IntRect(Vector2i(0,0), frame_size));
    }

    void Freeze() {
        this->freezeFrame = true;
    }

    void Unfreeze() {
        this->freezeFrame = false;
    }

    void ToggleFreeze() {
        this->freezeFrame = !this->freezeFrame;
    }

    void SetLoop(bool loop) {
        this->loop = loop;
    }

    void SetAnimationSpeed(float animation_speed) {
        this->animation_speed = animation_speed;
    }

    Sprite* GetFrame() {
        return this->sprite;
    }

    Vector2i GetSize() {
        return this->frame_size;
    }

    void NextFrame() {
        IntRect textureRect = this->sprite->getTextureRect();

        if (this->timer.getElapsedTime().asSeconds() > 1 / this->animation_speed) {
            if (textureRect.left + this->frame_size.x >= (this->frame_count * this->frame_size.x)) {
                if (loop) {
                    textureRect.left = 0;
                } else {
                    this->Freeze();
                }
            } else {
                if (!this->freezeFrame)
                    textureRect.left += this->frame_size.x;
            }
            
            this->timer.restart();
        }

        this->sprite->setTextureRect(textureRect);
    }
};