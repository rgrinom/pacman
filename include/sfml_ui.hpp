#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "ui.hpp"
#include "grid_sfml_drawer.hpp"
#include "pause_sfml_drawer.hpp"
#include "score_sfml_drawer.hpp"
#include "gameover_sfml_drawer.hpp"
#include "app_state.hpp"

class SfmlUI: public UI {
 public:
  SfmlUI(Logic& logic, Statistics& statistics, const Point& size);
  virtual Signal Run(const Logic::Event& logic_event) final;

 protected:
  virtual void Draw() final;
  virtual Signal CheckClicks() final;

 private:
  sf::RenderWindow window_;

  Point grid_size_;
  GridSfmlDrawer grid_drawer_;
  ScoreSfmlDrawer score_drawer_;
  PauseSfmlDrawer pause_drawer_;
  GameoverSfmlDrawer gameover_drawer_;

  bool IsKeyClicked(sf::Keyboard::Key key, uint32_t ind);
  std::vector<bool> is_pressed_;

  AppState state_;
};