#pragma once

#include "Component.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// SUPPORTED FILES: WAV, OGG, FLAC
class AudioPlayer : public Component {
private:
    SoundSource* source;
public:
    AudioPlayer() {
        this->source = new sf::Music();
    }

    void Play() {
        this->source->play();
    }

    void Stop() {
        this->source->stop();
    }

    void Pause() {
        this->source->pause();
    }

    void SetVolume(float volume) {
        this->source->setVolume(volume);
    }

    void SetPitch(float pitch) {
        this->source->setPitch(pitch);
    }

    void ChangeSource(string source_path) {
        sf::Music* music = dynamic_cast<Music*>(this->source);
        music->openFromFile(source_path);
    }

    void Trigger() override {}

}; 