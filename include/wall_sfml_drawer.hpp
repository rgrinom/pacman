#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "logic.hpp"

class WallSfmlDrawer {
 public:
  WallSfmlDrawer(Logic& logic, double block_size);
  void Draw(sf::RenderWindow& window, const Point& pos, const Point& pos_in_logic);

 private:
  Logic& logic_;

  sf::Texture texture_;
  sf::RectangleShape wall_;

  std::vector<int> dx = { 0, 1, 0, -1 };
  std::vector<int> dy = { -1, 0, 1, 0 };
};