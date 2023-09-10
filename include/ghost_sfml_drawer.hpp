#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "point.hpp"
#include "ghost.hpp"

class GhostSfmlDrawer {
 public:
  GhostSfmlDrawer(double block_size, const Ghost::GhostId& type);
  void Draw(sf::RenderWindow& window, const Point& pos,
            const Ghost::GhostState& state,
            const MovingObject::DirId& dir, bool paused);

 private:
  int step_;

  sf::Texture texture_;
  sf::Texture scared_texture_;

  sf::RectangleShape ghost_;
  sf::RectangleShape scared_ghost_;
};