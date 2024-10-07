#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

enum SoundType
{
  Music,
  Effect
};

class BaseAudible
{
protected:
  SoundType type;
  SoundSource *abstractSource = nullptr;
  /* Music audio source */
  string audioFile = "";
  /* Sound audio source */
  SoundBuffer audioBuffer;

  template <typename T>
  T *castSource()
  {
    return dynamic_cast<T *>(this->abstractSource);
  }

public:
  bool loop = false;
  float volume = 100;

  BaseAudible(string sourcePath, SoundType type = SoundType::Effect, bool loop = false)
  {
    this->loop = loop;
    this->type = type;

    if (type == SoundType::Effect)
    {
      this->audioBuffer = SoundBuffer();
      this->audioBuffer.loadFromFile(sourcePath);
      this->abstractSource = new Sound(this->audioBuffer);
    }
    else
    {
      sf::Music *rawMusic = new sf::Music();
      rawMusic->openFromFile(sourcePath);
      this->abstractSource = rawMusic;
    }
  }

  void setLoop(bool loop)
  {
    if (this->type == SoundType::Effect)
    {
      this->castSource<Sound>()->setLoop(loop);
    }
    else
    {
      this->castSource<sf::Music>()->setLoop(loop);
    }

    this->loop = loop;
  }

  void setVolume(float volume)
  {
    this->volume = volume;
    this->abstractSource->setVolume(this->volume);
  }

  void Play()
  {
    if (this->type == SoundType::Effect)
    {
      this->castSource<Sound>()->play();
    }
    else
    {
      this->castSource<sf::Music>()->play();
    }
  }

  void Pause()
  {
    if (this->type == SoundType::Effect)
    {
      this->castSource<Sound>()->pause();
    }
    else
    {
      this->castSource<sf::Music>()->pause();
    }
  }

  void Stop()
  {
    if (this->type == SoundType::Effect)
    {
      this->castSource<Sound>()->stop();
    }
    else
    {
      this->castSource<sf::Music>()->stop();
    }
  }
};