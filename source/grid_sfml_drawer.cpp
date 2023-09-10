#include "../include/grid_sfml_drawer.hpp"

GridSfmlDrawer::GridSfmlDrawer
    (Logic& logic, const Point& roi_pos, const Point& roi_size)
    : logic_(logic),
      roi_pos_(roi_pos),
      roi_size_(roi_size),
      block_size_(roi_size_.x / logic_.GetGridSize().x),
      wall_drawer_(logic, block_size_),
      buff_drawer_(block_size_),
      coin_drawer_(block_size_),
      pacman_drawer_(block_size_),
      red_ghost_drawer_(block_size_, Ghost::GhostId::Red),
      pink_ghost_drawer_(block_size_, Ghost::GhostId::Pink) {
}

void GridSfmlDrawer::Draw(sf::RenderWindow& window, bool paused) {
  DrawGrid(window);
  DrawPacman(window, paused);
  DrawGhosts(window, paused);
}

void GridSfmlDrawer::DrawGrid(sf::RenderWindow& window) {
  for (int32_t y = 0; y < logic_.GetGridSize().y; ++y) {
    for (int32_t x = 0; x < logic_.GetGridSize().x; ++x) {
      Grid::ObjectId ret = logic_.GridAt(Point(x, y));
      Point pos(x * block_size_ + block_size_ / 2,
                y * block_size_ + block_size_ / 2);
      pos += roi_pos_;
      switch (ret) {
        case Grid::ObjectId::Wall:
          wall_drawer_.Draw(window, pos, Point(x, y));
          break;
        case Grid::ObjectId::Buff:
          buff_drawer_.Draw(window, pos);
          break;
        case Grid::ObjectId::Coin:
          coin_drawer_.Draw(window, pos);
          break;
      }
    }
  }
}

void GridSfmlDrawer::DrawPacman(sf::RenderWindow& window, bool paused) {
  Point pacman_pos = logic_.GetPacmanPos();
  pacman_drawer_.Draw(window, roi_pos_ + pacman_pos * block_size_,
                      logic_.GetPacmanDirId(), paused);
}

void GridSfmlDrawer::DrawGhosts(sf::RenderWindow& window, bool paused) {
  uint32_t ghosts_cnt = logic_.GetGhostsCnt();
  for (uint32_t cur_ghost = 0; cur_ghost < ghosts_cnt; ++cur_ghost) {
    Point pos = logic_.GetGhostPos(cur_ghost) * block_size_;
    Ghost::GhostId type = logic_.GetGhostType(cur_ghost);
    Ghost::GhostState state = logic_.GetGhostState(cur_ghost);
    MovingObject::DirId dir = logic_.GetGhostDirId(cur_ghost);

    if (type == Ghost::GhostId::Red) {
      red_ghost_drawer_.Draw(window, pos, state, dir, paused);
    } else if (type == Ghost::GhostId::Pink) {
      pink_ghost_drawer_.Draw(window, pos, state, dir, paused);
    }
  }
}