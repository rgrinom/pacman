#include "../include/pacman_sfml_drawer.hpp"

PacmanSfmlDrawer::PacmanSfmlDrawer(double block_size): step_(0) {
  if (!texture_.loadFromFile("../content/images/pacman.png")) {
    std::cout << "Can't open pacman texture\n";
  }

  double pacman_size = std::max(block_size, 1.0);
  pacman_.setSize(sf::Vector2f(pacman_size, pacman_size));
  pacman_.setOrigin(pacman_size / 2, pacman_size / 2);
  pacman_.setFillColor(sf::Color(255, 255, 0));
  pacman_.setTexture(&texture_);
}

void PacmanSfmlDrawer::Draw(sf::RenderWindow& window, const Point& pos,
                            const MovingObject::DirId& dir, bool paused) {
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
    pacman_.setTextureRect(sf::IntRect(16 * (step_ / 4), 16 * dir_shift, 16, 16));
    step_ = (step_ + 1) % 8;
  }

  pacman_.setPosition(pos.x, pos.y);
  window.draw(pacman_);
}