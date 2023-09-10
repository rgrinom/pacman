#pragma once

#include "sounds.hpp"
#include "sfml_sound_player.hpp"

class SfmlSounds: public Sounds {
 public:
  SfmlSounds();
  virtual void Run(const Logic::Event logic_event) final;
  virtual void Mute() final;

 private:
  SfmlSoundPlayer level_started_;
  SfmlSoundPlayer money_eaten_;
  SfmlSoundPlayer ghost_eaten_;
  SfmlSoundPlayer pacman_died_;
};