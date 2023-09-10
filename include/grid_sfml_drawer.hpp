#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "point.hpp"
#include "logic.hpp"
#include "wall_sfml_drawer.hpp"
#include "buff_sfml_drawer.hpp"
#include "coin_sfml_drawer.hpp"
#include "pacman_sfml_drawer.hpp"
#include "ghost_sfml_drawer.hpp"

class GridSfmlDrawer{
 public:
  GridSfmlDrawer(Logic& logic, const Point& roi_pos, const Point& roi_size);
  void Draw(sf::RenderWindow& window, bool paused);

 private:
  void DrawGrid(sf::RenderWindow& window);
  void DrawPacman(sf::RenderWindow& window, bool paused);
  void DrawGhosts(sf::RenderWindow& window, bool paused);

  Logic& logic_;
  Point roi_pos_;
  Point roi_size_;
  double block_size_;

  WallSfmlDrawer wall_drawer_;
  BuffSfmlDrawer buff_drawer_;
  CoinSfmlDrawer coin_drawer_;
  PacmanSfmlDrawer pacman_drawer_;
  GhostSfmlDrawer red_ghost_drawer_;
  GhostSfmlDrawer pink_ghost_drawer_;
};