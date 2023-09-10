#include "../include/score_sfml_drawer.hpp"

ScoreSfmlDrawer::ScoreSfmlDrawer(Statistics& statistics, const Point& roi_pos,
                                 const Point& roi_size)
    : statistics_(statistics),
      roi_pos_(roi_pos),
      roi_size_(roi_size) {
  if (!bg_texture_.loadFromFile("../content/images/score.png")) {
    std::cout << "Can't load score texture\n";
  }
  if (!pacman_texture_.loadFromFile("../content/images/pacman.png")) {
    std::cout << "Can't load pacman texture for statistics\n";
  }
  if (!font_.loadFromFile("../content/fonts/texgyrepagella-math.otf")) {
    std::cout << "Can't load font\n";
  }

  bg_rect_.setSize(sf::Vector2f(roi_size_.x, roi_size_.y));
  bg_rect_.setPosition(sf::Vector2f(roi_pos_.x, roi_pos_.y));
  bg_rect_.setFillColor(sf::Color(255, 255, 255));
  bg_rect_.setTexture(&bg_texture_);

  pacman_size_ = roi_size_.y * 1.0 / 5.0;
  pacman_rect_.setSize(sf::Vector2f(pacman_size_, pacman_size_));
  pacman_rect_.setFillColor(sf::Color(255, 255, 255));
  pacman_rect_.setTexture(&pacman_texture_);
  pacman_rect_.setTextureRect(sf::IntRect(16 * 0, 16 * 1, 16, 16));

  score_.setFont(font_);
  score_.setCharacterSize(roi_size_.y * 1.0 / 6.0);
  score_.setFillColor(sf::Color(255, 255, 255));
  score_.setPosition(sf::Vector2f(roi_pos_.x + roi_size_.x * 360.0 / 600.0,
                                  roi_pos_.y + roi_size_.y * 30.0 / 200.0));
  
  level_.setFont(font_);
  level_.setCharacterSize(roi_size_.y * 1.0 / 6.0);
  level_.setFillColor(sf::Color(255, 255, 255));
  level_.setPosition(sf::Vector2f(roi_pos_.x + roi_size_.x * 540.0 / 600.0,
                                  roi_pos_.y + roi_size_.y * 30.0 / 200.0));
}

void ScoreSfmlDrawer::Draw(sf::RenderWindow& window) {
  window.draw(bg_rect_);

  for (int live = 0; live < statistics_.GetLives(); ++live) {
    pacman_rect_.setPosition(
      sf::Vector2f(roi_pos_.x + roi_size_.x * 120.0 / 600.0 + live * (pacman_size_ + roi_size_.x * 20.0 / 600.0),
                   roi_pos_.y + roi_size_.y * 30.0 / 200.0));
    window.draw(pacman_rect_);
  }

  score_.setString(std::to_string(statistics_.GetScore()));
  window.draw(score_);

  level_.setString(std::to_string(statistics_.GetLevel()));
  window.draw(level_);
}