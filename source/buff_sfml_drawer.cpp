#include "../include/buff_sfml_drawer.hpp"

BuffSfmlDrawer::BuffSfmlDrawer(double block_size) {
  double buff_radius = std::max(block_size / 4, 1.0);
  buff_.setRadius(buff_radius);
  buff_.setOrigin(buff_radius, buff_radius);
  buff_.setFillColor(sf::Color(255, 255, 0));
}

void BuffSfmlDrawer::Draw(sf::RenderWindow& window, const Point& pos) {
  buff_.setPosition(pos.x, pos.y);
  window.draw(buff_);
}