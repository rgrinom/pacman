#include "../include/pause_sfml_drawer.hpp"

PauseSfmlDrawer::PauseSfmlDrawer(const Point& roi_pos, const Point& roi_size) {
  if (!texture_.loadFromFile("../content/images/pause.png")) {
    std::cout << "Can't load pause texture\n";
  }

  rect_.setSize(sf::Vector2f(roi_size.x, roi_size.y));
  rect_.setPosition(sf::Vector2f(roi_pos.x, roi_pos.y));
  rect_.setFillColor(sf::Color(255, 255, 255, 150));
  rect_.setTexture(&texture_);
}

void PauseSfmlDrawer::Draw(sf::RenderWindow& window) { window.draw(rect_); }