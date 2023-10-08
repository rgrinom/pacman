#pragma once

#include <string>
#include <iostream>

#include <SFML/Audio.hpp>

class SfmlSoundPlayer {
 public:
  SfmlSoundPlayer(const std::string& file_name, bool wait_for_end = false);
  void Play();
  void Stop();

 private:
  sf::SoundBuffer buffer_;
  sf::Sound sound_;
  bool wait_for_end_;
};