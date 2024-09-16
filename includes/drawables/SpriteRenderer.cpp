#pragma once

#include "BaseDrawable.cpp"
#include "../Profiler.cpp"
#include <iostream>

using namespace std;

class Animation {
private:
  Vector2i frameSize;
  Texture texture;
  Sprite* sprite = nullptr;
  uint frameCount;
  bool loop;
public:
  int currentFrame = 0;

  Animation(string pathToTexture, Vector2i frameSize, uint frameCount, bool loop = true) {
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

  void setLoop(bool loop) {
      this->loop = loop;
  }

  Sprite* getSprite() {
      return this->sprite;
  }

  Vector2i getSize() {
    return this->frameSize;
  }

  uint getFrameCount() {
    return this->frameCount;
  }

  void NextFrame() {
    if (this->sprite == nullptr) return;

    IntRect textureRect = this->sprite->getTextureRect();

    if (textureRect.left + this->frameSize.x >= (int)(this->frameCount * this->frameSize.x)) {
      if (loop) {
        textureRect.left = 0;
        this->currentFrame = 0;
      }
    } else {
      textureRect.left += this->frameSize.x;
      this->currentFrame++;
    }

    this->sprite->setTextureRect(textureRect);
  }
};

class SpriteRenderer : public BaseDrawable {
private:
  Animation* animation = nullptr;
  bool freezeFrame = false;
  float animationSpeed = 1;
  Clock timer;
public:
  SpriteRenderer(Animation* animation = nullptr) {
    if (animation != nullptr) {
      this->changeAnimation(animation);
    }

    this->addDrawable(this->drawable);
  }

  virtual void freeze() final {
    this->freezeFrame = true;
  }

  virtual void unfreeze() final {
    this->freezeFrame = false;
  }

  virtual void toggleFreeze() final {
    this->freezeFrame = !this->freezeFrame;
  }

  virtual void setAnimationSpeed(float animationSpeed) final {
    this->animationSpeed = animationSpeed;
  }

  virtual void changeAnimation(Animation* animation) final {
    if (animation == nullptr) {
      Profiler::Warning("[SpriteRenderer] Trying to assign an animation with value of nullptr");
      return;
    }

    this->animation = animation;
    this->drawable = animation->getSprite();
    
    this->setAnimationSpeed(animation->getFrameCount());
    this->setSize((Vector2f)animation->getSize());
    this->unfreeze();

    this->animation->currentFrame = 0;
  }

  void onUpdate() {
    if (this->animation == nullptr || freezeFrame) return;

    if (this->timer.getElapsedTime().asSeconds() > (1 / this->animationSpeed)) {
      this->animation->NextFrame();
      this->timer.restart();
    }
  }
};