#pragma once
#include <SFML/Audio.hpp>
#include "Alerts.cpp"
#include <iostream>

using namespace std;
using namespace sf;

class AudioPlayer {
private:
  Music* music = nullptr;

  void Validate() {
    if (this->music == nullptr) Alerts::Error("Trying to control an AudioPlayer without any audio file set!");
  }

public:
  AudioPlayer(string source_path = "") {
    this->music = new Music();
    if (!this->music->openFromFile(source_path)) {
      Alerts::Error("AudioPlayer couldn't find the file in the path you specified: "+ source_path);
    }
  }

  void Play() {
    this->Validate();
    this->music->play();
  }

  void Stop() {
    this->Validate();
    this->music->stop();
  }

  void SetLoop(bool loop = false) {
    this->Validate();
    this->music->setLoop(loop);
  }
};