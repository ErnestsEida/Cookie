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

public:
  bool loop = false;

  BaseAudible(string sourcePath, SoundType type = SoundType::Effect, bool loop = false)
  {
    this->loop = loop;
    this->type = type;
  }
};