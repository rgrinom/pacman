#include "../include/ghost_sfml_drawer.hpp"

GhostSfmlDrawer::GhostSfmlDrawer(double block_size,
                                 const Ghost::GhostId& type): step_(0) {
  std::string texture_name;
  if (type == Ghost::GhostId::Red) {
    texture_name = "red_ghost.png";
  } else if (type == Ghost::GhostId::Pink) {
    texture_name = "pink_ghost.png";
  }

  if (!texture_.loadFromFile("../content/images/" + texture_name)) {
    std::cout << "Can't load ghost texture\n";
  }

  if (!scared_texture_.loadFromFile("../content/images/scared_ghost.png")) {
    std::cout << "Can't load scared ghost texture\n";
  }

  double ghost_size = std::max(block_size, 1.0);
  ghost_.setSize(sf::Vector2f(ghost_size, ghost_size));
  ghost_.setOrigin(ghost_size / 2, ghost_size / 2);
  ghost_.setTexture(&texture_);

  scared_ghost_.setSize(sf::Vector2f(ghost_size, ghost_size));
  scared_ghost_.setOrigin(ghost_size / 2, ghost_size / 2);
  scared_ghost_.setTexture(&scared_texture_);
}

void GhostSfmlDrawer::Draw(sf::RenderWindow& window, const Point& pos,
                           const Ghost::GhostState& state,
                           const MovingObject::DirId& dir, bool paused) {

  sf::Color fill_color = sf::Color(255, 255, 255);
  if (state == Ghost::GhostState::Reviving) {
    fill_color.a = 150;
  }

  if (!paused) {
    int dir_shift;
    if (dir == MovingObject::DirId::Right) {
      dir_shift = 0;
    } else if (dir == MovingObject::DirId::Left) {
      dir_shift = 1;
    } else if (dir == MovingObject::DirId::Up) {
      dir_shift = 2;
    } else {
      dir_shift = 3;
    }
    scared_ghost_.setTextureRect(sf::IntRect(16 * step_, 16 * dir_shift, 16, 16));
    ghost_.setTextureRect(sf::IntRect(16 * step_, 16 * dir_shift, 16, 16));
    step_ = (step_ + 1) % 2;
  }

  if (state == Ghost::GhostState::RunningAway) {
    scared_ghost_.setFillColor(fill_color);
    scared_ghost_.setPosition(pos.x, pos.y);
    window.draw(scared_ghost_);
  } else {
    ghost_.setFillColor(fill_color);
    ghost_.setPosition(pos.x, pos.y);
    window.draw(ghost_);
  }
}