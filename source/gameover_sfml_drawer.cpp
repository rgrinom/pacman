#include "../include/gameover_sfml_drawer.hpp"

GameoverSfmlDrawer::GameoverSfmlDrawer
    (Statistics& statistics, const Point& roi_pos, const Point& roi_size)
    : statistics_(statistics),
      roi_pos_(roi_pos),
      roi_size_(roi_size) {
  if (!bg_texture_.loadFromFile("../content/images/game_over.png")) {
    std::cout << "Can't load score texture\n";
  }
  if (!font_.loadFromFile("../content/fonts/texgyrepagella-math.otf")) {
    std::cout << "Can't load font\n";
  }

  bg_rect_.setSize(sf::Vector2f(roi_size_.x, roi_size_.y));
  bg_rect_.setPosition(sf::Vector2f(roi_pos_.x, roi_pos_.y));
  bg_rect_.setFillColor(sf::Color(255, 255, 255));
  bg_rect_.setTexture(&bg_texture_);

  score_.setFont(font_);
  score_.setCharacterSize(roi_size_.y * 1.0 / 6.0);
  score_.setFillColor(sf::Color(255, 255, 255));
}

void GameoverSfmlDrawer::Draw(sf::RenderWindow& window) {
  window.draw(bg_rect_);

  score_.setString(std::to_string(statistics_.GetScore()));
  sf::FloatRect textRect = score_.getLocalBounds();
  score_.setOrigin(textRect.left + textRect.width / 2.0, textRect.top);
  score_.setPosition(sf::Vector2f(roi_pos_.x + roi_size_.x * 1.0 / 2.0,
                                  roi_pos_.y + roi_size_.y * 300.0 / 800.0));
  window.draw(score_);
}