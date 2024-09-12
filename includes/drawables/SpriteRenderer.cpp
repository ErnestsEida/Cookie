#pragma once

#include "BaseDrawable.cpp"
#include "../Profiler.cpp"
#include <iostream>

using namespace std;

class Animation {
private:
  float animation_speed;
  Vector2i frameSize;
  Texture texture;
  Sprite* sprite = nullptr;
  bool freezeFrame = false;
  int frameCount;
  Clock timer;
  bool loop;
public:
  int currentFrame = 0;

  Animation(string pathToTexture, Vector2i frameSize, int frameCount, bool loop = true) {
    this->animation_speed = frameCount;
    this->frameCount = frameCount;
    this->frameSize = frameSize;
    this->loop = loop;

    this->texture = Texture();
    bool textureLoaded = this->texture.loadFromFile(pathToTexture);
    if (textureLoaded) {
      this->sprite = new Sprite(this->texture, IntRect(Vector2i(0, 0), frameSize));
    } else {
      Profiler::Warning("[ANIMATION] Couldn't set texture from path '" + pathToTexture + "'");
    }
  }

  void freeze() {
      this->freezeFrame = true;
  }

  void unfreeze() {
      this->freezeFrame = false;
  }

  void toggleFreeze() {
      this->freezeFrame = !this->freezeFrame;
  }

  void setLoop(bool loop) {
      this->loop = loop;
  }

  void setAnimationSpeed(float animation_speed) {
      this->animation_speed = animation_speed;
  }

  Sprite* getSprite() {
      return this->sprite;
  }

  void NextFrame() {
    if (this->sprite == nullptr) return;

    IntRect textureRect = this->sprite->getTextureRect();

    if (this->timer.getElapsedTime().asSeconds() > 1 / this->animation_speed) {
        if (textureRect.left + this->frameSize.x >= (this->frameCount * this->frameSize.x)) {
            if (loop) {
                textureRect.left = 0;
                this->currentFrame = 0;
            } else {
                this->freeze();
            }
        } else {
            if (!this->freezeFrame) {
                textureRect.left += this->frameSize.x;
                this->currentFrame++;
            }
        }
        this->timer.restart();
    }

    this->sprite->setTextureRect(textureRect);
  }
};

class SpriteRenderer : public BaseDrawable {
private:
  Animation* animation = nullptr;
public:
  SpriteRenderer(Animation* animation = nullptr) {
    if (animation != nullptr) {
      this->changeAnimation(animation);
    }

    this->addDrawable(this->drawable);
  }

  void changeAnimation(Animation* animation) {
    this->animation = animation;
    this->drawable = animation->getSprite();
  }

  void onUpdate() {
    if (this->animation != nullptr) {
      this->animation->NextFrame();
    }
  }
};