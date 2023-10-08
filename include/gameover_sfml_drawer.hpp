#pragma once

#include <SFML/Graphics.hpp>

#include "statistics.hpp"
#include "point.hpp"

class GameoverSfmlDrawer {
 public:
  GameoverSfmlDrawer(Statistics& statistics, const Point& roi_pos,
                     const Point& roi_size);
  void Draw(sf::RenderWindow& window);

 private:
  Statistics& statistics_;
  Point roi_pos_;
  Point roi_size_;

  sf::Texture bg_texture_;
  sf::RectangleShape bg_rect_;

  sf::Font font_;
  sf::Text score_;
};