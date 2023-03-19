#pragma once

#include <SFML/Graphics.hpp>

#include "ui.hpp"

class SfmlUI: public UI {
 public:
  SfmlUI(Logic& logic, const Point& size);
  virtual bool Run() final;

 protected:
  virtual void Draw() final;
  virtual void DrawGrid() final;
  virtual void DrawWall(const Point& pos) final;
  virtual void DrawBuff(const Point& pos) final;
  virtual void DrawCoin(const Point& pos) final;
  virtual void DrawPacman() final;
  virtual void DrawGhosts() final;
  virtual void DrawRedGhost(const Point& pos) final;

  virtual void CheckClicks() final;

 private:
  double block_size_;
  sf::RenderWindow window_;

  bool IsKeyClicked(sf::Keyboard::Key key, uint32_t ind);
  std::vector<bool> is_pressed_;

  sf::RectangleShape wall_;
  sf::CircleShape buff_;
  sf::CircleShape coin_;
  sf::CircleShape pacman_;
  sf::CircleShape red_ghost_;

  void LoadSfmlObjects();
};