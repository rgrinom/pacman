#include "../include/sfml_sounds.hpp"

SfmlSounds::SfmlSounds()
    : level_started_("pacman_beginning.wav", true),
      money_eaten_("pacman_chomp.wav", false),
      ghost_eaten_("pacman_eatghost.wav", false),
      pacman_died_("pacman_death.wav", true) {}

void SfmlSounds::Run(const Logic::Event logic_event) {
  if (muted_) {
    return;
  }

  switch (logic_event) {
    case Logic::Event::LevelStarted:
      money_eaten_.Stop();
      ghost_eaten_.Stop();
      level_started_.Play();
      break;
    case Logic::Event::MoneyEaten:
      money_eaten_.Play();
      break;
    case Logic::Event::GhostEaten:
      ghost_eaten_.Play();
      break;
    case Logic::Event::PacmanDied:
      money_eaten_.Stop();
      ghost_eaten_.Stop();
      pacman_died_.Play();
      break;
    default:
      break;
  }
}

void SfmlSounds::Mute() {
  if (!muted_) {
    level_started_.Stop();
    money_eaten_.Stop();
    ghost_eaten_.Stop();
    pacman_died_.Stop();
  }
  muted_ = !muted_;
}