#include "../include/coin_sfml_drawer.hpp"

CoinSfmlDrawer::CoinSfmlDrawer(double block_size) {
  double coin_radius = std::max(block_size / 10, 1.0);
  coin_.setRadius(coin_radius);
  coin_.setOrigin(coin_radius, coin_radius);
  coin_.setFillColor(sf::Color(255, 255, 0));
}

void CoinSfmlDrawer::Draw(sf::RenderWindow& window, const Point& pos) {
  coin_.setPosition(pos.x, pos.y);
  window.draw(coin_);
}