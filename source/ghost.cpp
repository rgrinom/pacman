#include "../include/ghost.hpp"

Ghost::GhostId Ghost::GetType() const { return type_; }

void Ghost::Move(const Grid& grid, Point pacman_pos) {
  SetTarget(pacman_pos);
  pacman_pos = (floor(pacman_pos) + ceil(pacman_pos)) / 2;
  Point my_pos = (floor(pos_) + ceil(pos_)) / 2;
  std::vector<std::vector<bool>> visited(grid.GetSize().y,
                                         std::vector<bool>(grid.GetSize().x, 0));
  std::queue<Point> bfs_points;
  bfs_points.push(pacman_pos);
  visited[pacman_pos.y][pacman_pos.x] = true;
  std::vector<Point> shifts = {Point(-1,  0),
                               Point( 1,  0),
                               Point( 0, -1),
                               Point( 0,  1)};
  try {
    while (!bfs_points.empty()) {
      Point cur_p = bfs_points.front();
      bfs_points.pop();
      for (uint32_t i = 0; i < shifts.size(); ++i) {
        Point next_p = cur_p + shifts[i];
        if (next_p.y < 0 || next_p.y > grid.GetSize().y) {
          continue;
        }
        if (next_p.x < 0 || next_p.x > grid.GetSize().x) {
          continue;
        }
        if (grid.At(next_p) == Grid::ObjectId::Wall) {
          continue;
        }
        if (visited[next_p.y][next_p.x]) {
          continue;
        }
        if (next_p == my_pos) {
          if (i == 0) {
            SetNextDir(DirId::Right);
          } else if (i == 1) {
            SetNextDir(DirId::Left);
          } else if (i == 2) {
            SetNextDir(DirId::Down);
          } else if (i == 3) {
            SetNextDir(DirId::Up);
          }
          throw 1;
        }
        visited[next_p.y][next_p.x] = true;
        bfs_points.push(next_p);
      }
    }
  } catch (...) {

  }


  // // TODO: this algo is slow. Should write mitm bfs

  MovingObject::Move(grid);
}