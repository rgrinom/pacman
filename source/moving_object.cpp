#include "../include/moving_object.hpp"

const double MovingObject::size = 0.999;

void MovingObject::Load(const std::string& config_file) {
  std::ifstream config;
  config.open("../content/" + config_file);
  int16_t spawn_dir;
  config >> spawn_pos_ >> spawn_dir >> speed_;
  spawn_dir_id_ = DirId(spawn_dir);
  Reset();
  config.close();
}

void MovingObject::SetDir(DirId dir_id) {
  dir_id_ = dir_id;
  if (dir_id_ == DirId::Left) {
    dir_ = Point(-1, 0);
  } else if (dir_id_ == DirId::Right) {
    dir_ = Point(1, 0);
  } else if (dir_id_ == DirId::Up) {
    dir_ = Point(0, -1);
  } else if (dir_id_ == DirId::Down) {
    dir_ = Point(0, 1);
  }
}

void MovingObject::SetNextDir(DirId next_dir_id) { next_dir_id_ = next_dir_id; }

void MovingObject::Move(const Grid& grid) {
  if (next_dir_id_ == cur_dir_id_) {
    TryMove(grid);
    return;
  }

  SetDir(next_dir_id_);
  if (TryMove(grid)) {
    cur_dir_id_ = next_dir_id_;
    return;
  }
  SetDir(cur_dir_id_);
  TryMove(grid);
}

bool MovingObject::TryMove(const Grid& grid) {
  Point new_pos = pos_ + dir_ * speed_;
  std::vector<Point> collision_points = {new_pos + Point(-size / 2, -size / 2),
                                         new_pos + Point( size / 2, -size / 2),
                                         new_pos + Point( size / 2,  size / 2),
                                         new_pos + Point(-size / 2,  size / 2)};
  bool ret = true;
  for (const Point& collision_point : collision_points) {
    if (grid.At(collision_point) == Grid::ObjectId::Wall) {
      Point cell_center = (floor(new_pos) + ceil(new_pos)) / 2;
      if (dir_id_ == DirId::Left || dir_id_ == DirId::Right) {
        new_pos.x = cell_center.x;
      } else {
        new_pos.y = cell_center.y;
      }

      ret = false;
      break;
    }
  }
  if (new_pos.x < 0) {
    new_pos.x += grid.GetSize().x;
  }
  if (new_pos.x >= grid.GetSize().x) {
    new_pos.x -= grid.GetSize().x;
  }
  if (new_pos.y < 0) {
    new_pos.y += grid.GetSize().y;
  }
  if (new_pos.y >= grid.GetSize().y) {
    new_pos.y -= grid.GetSize().y;
  }
  pos_ = new_pos;
  return ret;
}

Point MovingObject::GetPos() const { return pos_; }

void MovingObject::Reset() {
  pos_ = spawn_pos_;
  cur_dir_id_ = spawn_dir_id_;
  next_dir_id_ = spawn_dir_id_;
  SetDir(cur_dir_id_);
}

bool MovingObject::Touches(const MovingObject& obj) const {
  return dist2(pos_, obj.pos_) <= size / 2;
}