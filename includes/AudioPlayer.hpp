#pragma once

#include <SFML/Audio.hpp>
#include "GameObject.hpp"

using namespace sf;

class AudioPlayer : public GameObject {
private:
    SoundSource* source; 
public:
    AudioPlayer() : GameObject(0, 0) {}
    AudioPlayer(float x, float y) : GameObject(x, y) {}

    void setSource(SoundSource* source) {
        this->source = source;
    }

    void setSource(string pathToSource, bool isMusic = false) {
        // CREATE A SOUND 
    }

    // CONTROLLING AUDIO GOES BELOW ...
    void Play() { this->source->play(); }

    void Pause() { this->source->pause(); }

    void Stop() { this->source->stop(); }

    float getVolume() const { return this->source->getVolume(); }

    void setVolume(float volume) const { this->source->setVolume(volume); }

    float getPitch() const { return this->source->getPitch(); }

    void setPitch(float pitch) { this->source->setPitch(pitch); }

};