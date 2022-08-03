#pragma once

#include <SFML/Graphics.hpp>
#include "./Animation.hpp"
#include "Component.hpp"

#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class SpriteRenderer : public Component {
private:
    float frame_speed;
    Clock clock;
    Animation* animation;
public:
    SpriteRenderer(){ // SETS SPRITE COUNT TO NULL TO ALLOW GAMEOBJECT TO CALL ITERATE() WITHOUT ANY SPRITES GIVEN
        this->animation = NULL;
    }

    // SETTERS
    void SetFramespeed(float frame_speed){
        this->frame_speed = frame_speed;
    }

    void SetAnimation(Animation* animation){
        this->ClearDrawables();
        this->animation = animation;
        this->SetFramespeed(this->animation->GetSpriteCount());
        this->AddDrawable(this->animation->GetSprite());
    }

    // MISC
    void Trigger() override {
        if (this->animation != NULL) {
            if(this->clock.getElapsedTime().asSeconds() > 1.0 / this->frame_speed){
                this->animation->NextSprite();
                clock.restart();
            }
        }
    }
};