#pragma once

#include <SFML/Graphics.hpp>

#include "point.hpp"

class PauseSfmlDrawer {
 public:
  PauseSfmlDrawer(const Point& roi_pos, const Point& roi_size);
  void Draw(sf::RenderWindow& window);

 private:
  sf::Texture texture_;
  sf::RectangleShape rect_;
};