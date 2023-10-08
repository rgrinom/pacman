#include "../include/sfml_sound_player.hpp"

SfmlSoundPlayer::SfmlSoundPlayer(const std::string& file_name, bool wait_for_end)
    : wait_for_end_(wait_for_end) {
  if (!buffer_.loadFromFile("../content/sounds/" + file_name)) {
    std::cout << "Can't load " << file_name << " sound\n";
  }

  sound_.setBuffer(buffer_);
}

void SfmlSoundPlayer::Play() {
  if (sound_.getStatus() == sf::Sound::Playing) {
    return;
  }

  sound_.play();

  if (!wait_for_end_) {
    return;
  }

  while (sound_.getStatus() == sf::Sound::Playing) {}
}

void SfmlSoundPlayer::Stop() { sound_.stop(); }