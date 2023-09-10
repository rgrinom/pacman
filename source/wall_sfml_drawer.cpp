#include "../include/wall_sfml_drawer.hpp"

WallSfmlDrawer::WallSfmlDrawer(Logic& logic, double block_size)
    : logic_(logic) {
  if (!texture_.loadFromFile("../content/images/wall.png")) {
    std::cout << "Can't load wall texture\n";
  }
  wall_.setSize(sf::Vector2f(block_size, block_size));
  wall_.setOrigin(block_size / 2, block_size / 2);
  wall_.setFillColor(sf::Color(255, 255, 255));
  wall_.setTexture(&texture_);
}

void WallSfmlDrawer::Draw(sf::RenderWindow& window, const Point& pos,
                          const Point& pos_in_logic) {
  wall_.setPosition(pos.x, pos.y);

  int walls = 0;
  for (int i = 0; i < 4; ++i) {
    Point check_p = pos_in_logic + Point(dx[i], dy[i]);
    if (logic_.GridAt(check_p) == Grid::ObjectId::Wall) {
      walls += (1 << i);
    }
  }

  switch (walls) {
    case 6:
      wall_.setTextureRect(sf::IntRect(0, 0, 50, 50));
      break;
    case 14:
      wall_.setTextureRect(sf::IntRect(50, 0, 50, 50));
      break;
    case 12:
      wall_.setTextureRect(sf::IntRect(100, 0, 50, 50));
      break;
    case 7:
      wall_.setTextureRect(sf::IntRect(0, 50, 50, 50));
      break;
    case 13:
      wall_.setTextureRect(sf::IntRect(100, 50, 50, 50));
      break;
    case 3:
      wall_.setTextureRect(sf::IntRect(0, 100, 50, 50));
      break;
    case 11:
      wall_.setTextureRect(sf::IntRect(50, 100, 50, 50));
      break;
    case 9:
      wall_.setTextureRect(sf::IntRect(100, 100, 50, 50));
      break;
    case 15:
      wall_.setTextureRect(sf::IntRect(50, 50, 50, 50));
      break;
  }

  window.draw(wall_);
}