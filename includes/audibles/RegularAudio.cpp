#pragma once
#include "BaseAudible.cpp"

class RegularAudio : public BaseAudible
{
public:
  RegularAudio(string sourcePath, SoundType type) : BaseAudible(sourcePath, type) {}
};