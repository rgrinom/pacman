#include "../include/sfml_ui.hpp"

SfmlUI::SfmlUI(Logic& logic, const Point& size)
    : UI(logic), is_pressed_(4) {
  window_.create(sf::VideoMode(size.x, size.y), "Pacman");
  block_size_ = size.x / logic_.GetGridSize().x;
  LoadSfmlObjects();
}

void SfmlUI::LoadSfmlObjects() {
  wall_.setSize(sf::Vector2f(block_size_, block_size_));
  wall_.setOrigin(block_size_ / 2, block_size_ / 2);
  wall_.setFillColor(sf::Color(255, 255, 255));

  double buff_radius = std::max(block_size_ / 4, 1.0);
  buff_.setRadius(buff_radius);
  buff_.setOrigin(buff_radius, buff_radius);
  buff_.setFillColor(sf::Color(255, 255, 0));

  double coin_radius = std::max(block_size_ / 10, 1.0);
  coin_.setRadius(coin_radius);
  coin_.setOrigin(coin_radius, coin_radius);
  coin_.setFillColor(sf::Color(255, 255, 0));

  double pacman_radius = std::max(block_size_ / 2, 1.0);
  pacman_.setRadius(pacman_radius);
  pacman_.setOrigin(pacman_radius, pacman_radius);
  pacman_.setFillColor(sf::Color(255, 255, 0));

  double ghost_radius = std::max(block_size_ / 2, 1.0);
  red_ghost_.setRadius(ghost_radius);
  red_ghost_.setOrigin(ghost_radius, ghost_radius);
  red_ghost_.setFillColor(sf::Color(255, 0, 0));
}

bool SfmlUI::Run() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
      return false;
    }
  }
  CheckClicks();
  Draw();
  return true;
}

void SfmlUI::Draw() {
  window_.clear();
  DrawGrid();
  DrawGhosts();
  DrawPacman();
  window_.display();
}

void SfmlUI::DrawGrid() {
  for (int32_t y = 0; y < logic_.GetGridSize().y; ++y) {
    for (int32_t x = 0; x < logic_.GetGridSize().x; ++x) {
      Grid::ObjectId ret = logic_.GridAt(Point(x, y));
      Point pos(x * block_size_ + block_size_ / 2,
                y * block_size_ + block_size_ / 2);
      switch (ret) {
        case Grid::ObjectId::Wall:
          DrawWall(pos);
          break;
        case Grid::ObjectId::Buff:
          DrawBuff(pos);
          break;
        case Grid::ObjectId::Coin:
          DrawCoin(pos);
          break;
      }
    }
  }
}

void SfmlUI::DrawWall(const Point& pos) {
  wall_.setPosition(pos.x, pos.y);
  window_.draw(wall_);
}

void SfmlUI::DrawBuff(const Point& pos) {
  buff_.setPosition(pos.x, pos.y);
  window_.draw(buff_);
}

void SfmlUI::DrawCoin(const Point& pos) {
  coin_.setPosition(pos.x, pos.y);
  window_.draw(coin_);
}

void SfmlUI::DrawPacman() {
  Point pacman_pos = logic_.GetPacmanPos();
  pacman_.setPosition(pacman_pos.x * block_size_, pacman_pos.y * block_size_);
  window_.draw(pacman_);
}

void SfmlUI::DrawGhosts() {
  uint32_t ghosts_cnt = logic_.GetGhostsCnt();
  for (uint32_t cur_ghost = 0; cur_ghost < ghosts_cnt; ++cur_ghost) {
    Point cur_ghost_pos = logic_.GetGhostPos(cur_ghost) * block_size_;
    Ghost::GhostId cur_ghost_type = logic_.GetGhostType(cur_ghost);
    if (cur_ghost_type == Ghost::GhostId::Red) {
      DrawRedGhost(cur_ghost_pos);
    }
  }
}

void SfmlUI::DrawRedGhost(const Point& pos) {
  red_ghost_.setPosition(pos.x, pos.y);
  window_.draw(red_ghost_);
}

void SfmlUI::CheckClicks() {
  if (IsKeyClicked(sf::Keyboard::Left, 0)) {
    logic_.SetPacmanDir(MovingObject::DirId::Left);
  }
  if (IsKeyClicked(sf::Keyboard::Right, 1)) {
    logic_.SetPacmanDir(MovingObject::DirId::Right);
  }
  if (IsKeyClicked(sf::Keyboard::Up, 2)) {
    logic_.SetPacmanDir(MovingObject::DirId::Up);
  }
  if (IsKeyClicked(sf::Keyboard::Down, 3)) {
    logic_.SetPacmanDir(MovingObject::DirId::Down);
  }
}

bool SfmlUI::IsKeyClicked(sf::Keyboard::Key key, uint32_t ind) {
  if (sf::Keyboard::isKeyPressed(key)) {
    if (!is_pressed_[ind]) {
      is_pressed_[ind] = true;
      return true;
    }
  } else {
    is_pressed_[ind] = false;
  }
  return false;
}