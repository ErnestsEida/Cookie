// SUPPORTED FORMATS: .WAV, .OGG, .FLAC

#pragma once

#include "../includes/GameObject.hpp"
#include "../includes/Gametime.hpp"
#include "Child.hpp"
#include "../includes/GraphicsRenderer.hpp"
#include "../includes/AudioPlayer.hpp"

class Player : public GameObject {
private:
    const float GRAVITY = 9.71f;

    float speed = 150;
    int vsp = 0;
    AudioPlayer* audio;
public:
    Player(int x, int y) : GameObject(x, y) {
        this->setCollider(32, 32);
        GraphicsRenderer* renderer = new GraphicsRenderer(0, 0);
        renderer->addSprite("./demo/sprites/test.png", 32, 32, 4);
        renderer->setDrawableOrigin(0, 0);
        this->audio = new AudioPlayer();
        this->audio->setSource("./demo/sounds/random.wav");
        this->addChild(this->audio);
        this->addChild(renderer);
    }

    void OnStart() {}

    void OnUpdate() {
        float real_speed = speed * Gametime::deltaTime;
        if (Keyboard::isKeyPressed(Keyboard::Space)){
            this->audio->Play();
        }
        int hsp = Keyboard::isKeyPressed(Keyboard::D) - Keyboard::isKeyPressed(Keyboard::A);
        int vsp = Keyboard::isKeyPressed(Keyboard::S) - Keyboard::isKeyPressed(Keyboard::W);
        float real_x = hsp * real_speed;
        float real_y = vsp * real_speed;
        // vsp += GRAVITY;
        this->Move(real_x, real_y);
    }
};