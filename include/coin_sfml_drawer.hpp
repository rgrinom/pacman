#pragma once

#include <SFML/Graphics.hpp>

#include "point.hpp"

class CoinSfmlDrawer {
 public:
  CoinSfmlDrawer(double block_size);
  void Draw(sf::RenderWindow& window, const Point& pos);

 private:
  sf::CircleShape coin_;
};