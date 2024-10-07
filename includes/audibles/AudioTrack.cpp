#pragma once

#include <map>

#include "BaseAudible.cpp"
#include "../Profiler.cpp"

using namespace std;

struct AudioTrackSettings
{
  float volume = 100;
};

class AudioTrack
{
private:
  static map<string, AudioTrack *> lines;

  // Object variables
  vector<BaseAudible *> audibles = vector<BaseAudible *>();
  AudioTrackSettings settings = AudioTrackSettings();

  void refreshSettings()
  {
    for (BaseAudible *unit : this->audibles)
    {
      this->applySettingsToAudible(unit);
    }
  }

  void applySettingsToAudible(BaseAudible *audible)
  {
    audible->setVolume(this->settings.volume);
  }

public:
  static void registerTrack(string trackName)
  {
    AudioTrack::lines.insert(pair(trackName, new AudioTrack()));
  }

  static void appendAudible(string trackName, BaseAudible *audible)
  {
    try
    {
      AudioTrack *selectedTrack = AudioTrack::lines.at(trackName);
      selectedTrack->audibles.push_back(audible);
      selectedTrack->applySettingsToAudible(audible);
    }
    catch (out_of_range const &e)
    {
      Profiler::Warning("[AudioTrack] Track with name '" + trackName + "' is not registered");
    }
  }

  static void applySettings(string trackName)
  {
    try
    {
      AudioTrack::lines.at(trackName)->refreshSettings();
    }
    catch (out_of_range const &e)
    {
      Profiler::Warning("[AudioTrack] Trying to apply new settings for unregistered track '" + trackName + "'");
    }
  }

  static AudioTrackSettings *getTrackSettings(string trackName)
  {
    try
    {
      return &AudioTrack::lines.at(trackName)->settings;
    }
    catch (out_of_range const &e)
    {
      Profiler::Warning("[AudioTrack] Trying to access unregistered track '" + trackName + "' settings");
      return new AudioTrackSettings();
    }
  }
};

map<string, AudioTrack *> AudioTrack::lines = map<string, AudioTrack *>();