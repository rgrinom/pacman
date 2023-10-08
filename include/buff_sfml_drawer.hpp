#pragma once

#include <SFML/Graphics.hpp>

#include "point.hpp"

class BuffSfmlDrawer {
 public:
  BuffSfmlDrawer(double block_size);
  void Draw(sf::RenderWindow& window, const Point& pos);

 private:
  sf::CircleShape buff_;
};