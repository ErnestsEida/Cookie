#include <SFML/Graphics.hpp>
#include "./Animation.hpp"

#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class SpriteRenderer {
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
        this->animation = animation;
        this->SetFramespeed(this->animation->GetSpriteCount());
    }

    // GETTERS
    Sprite* GetSprite() const{
        return this->animation->GetSprite();
    }

    // MISC
    void Iterate() {
        if (this->animation != NULL) {
            if(this->clock.getElapsedTime().asSeconds() > 1.0 / this->frame_speed){
                this->animation->NextSprite();
                clock.restart();
            }
        }
    }
};