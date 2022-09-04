#pragma once

#include <SFML/Audio.hpp>
#include "GameObject.hpp"

using namespace sf;

class AudioPlayer : public GameObject {
private:
    Music* musicSlot = NULL;
    Sound* soundSlot = NULL;

    void eraseSlots() {
         this->musicSlot = NULL;
         this->soundSlot = NULL;
    }

    bool isMusic() { return this->musicSlot != NULL; }
    bool notEmpty() {
        if (this->musicSlot == NULL && this->soundSlot == NULL) {
            Alerts::WarningMessage("No audio source is set on AudioPlayer. It won't play until there is one!");
            return false;
        }
        return true;
    }
public:
    AudioPlayer() : GameObject(0, 0) {}
    AudioPlayer(float x, float y) : GameObject(x, y) {}

    void setSource(SoundSource* source, bool isMusic = false) {
        this->eraseSlots();

        if (isMusic)
            this->musicSlot = dynamic_cast<Music*>(source);
        else 
            this->soundSlot = dynamic_cast<Sound*>(source);
    }

    void setSource(string pathToSource, bool isMusic = false) {
        this->eraseSlots();
        if (isMusic) {
            this->musicSlot = new Music();
            if (!this->musicSlot->openFromFile(pathToSource)) {
                Alerts::ErrorMessage("Couldn't load source in AudioPlayer from \"" + pathToSource + "\"");
            }
        } else {

        }
    }

    // CONTROLLING AUDIO GOES BELOW ...
    void Play() { 
        if (this->notEmpty())
            this->isMusic() ? this->musicSlot->play() : this->soundSlot->play();
        else
            return; 
    }

    void Pause() {
        if (this->notEmpty())
            this->isMusic() ? this->musicSlot->pause() : this->soundSlot->pause();
        else
            return;
    }

    void Stop() {
        if (this->notEmpty())
            this->isMusic() ? this->musicSlot->stop() : this->soundSlot->stop();
        else
            return;
    }

    float getVolume() {
        if (this->notEmpty())
            return this->isMusic() ? this->musicSlot->getVolume() : this->soundSlot->getVolume();
        else
            return -1;
    }

    void setVolume(float volume) {
        if (this->notEmpty())
            this->isMusic() ? this->musicSlot->setVolume(volume) : this->soundSlot->setVolume(volume);
        else
            return;
    }

    float getPitch() {
        if (this->notEmpty())
            return this->isMusic() ? this->musicSlot->getPitch() : this->soundSlot->getPitch();
        else
            return -1;
    }

    void setPitch(float pitch) {
        if (this->notEmpty())
            this->isMusic() ? this->musicSlot->setPitch(pitch) : this->soundSlot->setPitch(pitch);
        else
            return;
    }

};