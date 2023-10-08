#pragma once

#include <SFML/Graphics.hpp>

#include "point.hpp"
#include "moving_object.hpp"

class PacmanSfmlDrawer {
 public:
  PacmanSfmlDrawer(double block_size);
  void Draw(sf::RenderWindow& window, const Point& pos,
            const MovingObject::DirId& dir, bool paused);

 private:
  int step_;

  sf::Texture texture_;
  sf::RectangleShape pacman_;
};