#pragma once

#include <cstdint>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "point.hpp"

class Grid {
 public:
  enum class ObjectId: int16_t {
    Nothing,
    Wall,
    Coin,
    Buff,
    Bonus,
  };

  Grid() = default;
  int32_t Load(const std::string& config_file);
  void Set(Point p, ObjectId obj);
  ObjectId At(Point p) const;
  Point GetSize() const;
  void Reset();

 private:
  bool is_constructed_;

  uint32_t width_, height_;
  std::vector<std::vector<ObjectId>> init_objects_;
  std::vector<std::vector<ObjectId>> objects_;
};