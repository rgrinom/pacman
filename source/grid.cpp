#include "../include/grid.hpp"

int32_t Grid::Load(const std::string& config_file) {
  std::ifstream config;
  config.open("../content/" + config_file);
  config >> width_ >> height_;
  init_objects_ = std::vector<std::vector<ObjectId>>(
      height_, std::vector<ObjectId>(width_, ObjectId::Nothing));
  
  int32_t coins_cnt = 0;
  for (uint32_t y = 0; y < height_; ++y) {
    for (uint32_t x = 0; x < width_; ++x) {
      uint16_t cell;
      config >> cell;
      if (cell == 1) {
        init_objects_[y][x] = ObjectId::Wall;
      } else if (cell == 2) {
        init_objects_[y][x] = ObjectId::Coin;
        ++coins_cnt;
      } else if (cell == 3) {
        init_objects_[y][x] = ObjectId::Buff;
      } else if (cell == 4) {
        init_objects_[y][x] = ObjectId::Bonus;
      }
    }
  }
  Reset();
  config.close();
  return coins_cnt;
}

void Grid::Set(Point p, ObjectId obj) {
  p = floor(p);
  if (p.x < 0 || p.x >= width_ || p.y < 0 || p.y >= height_) {
    return;
  }
  objects_[p.y][p.x] = obj;
}

Grid::ObjectId Grid::At(Point p) const {
  p = floor(p);
  if (p.x < 0 || p.x >= width_ || p.y < 0 || p.y >= height_) {
    return ObjectId::Nothing;
  }
  return objects_[p.y][p.x];
}

Point Grid::GetSize() const { return Point(width_, height_); }

void Grid::Reset() { objects_ = init_objects_; }